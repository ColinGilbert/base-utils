#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <algorithm>
#include <vector>

#include <noob/fast_hashtable/fast_hashtable.hpp>
#include <noob/component/component.hpp>
#include <noob/bitpack/bitpack.hpp>
//#include <noob/strings/strings.hpp>

#include <rdestl/sort.h>

namespace noob
{
	typedef noob::handle<uint32_t> node_handle;

	class digraph
	{
		public:

			digraph() noexcept(true) : ready(false) {}

			// Backed by uint64_t bitmask: First 32 bits = from, second 32 bits = to.
			class edge
			{
				friend class digraph;

				public:

				edge() noexcept(true) : val(0) {}

				void set_from(const noob::node_handle from) noexcept(true)
				{
					std::tuple<uint32_t, uint32_t> unpacked = noob::pack_64_to_32(val);
					val = pack_32_to_64(from.index(), std::get<1>(unpacked));
				}

				void set_to(const noob::node_handle to) noexcept(true)
				{
					std::tuple<uint32_t, uint32_t> unpacked = noob::pack_64_to_32(val);
					val = pack_32_to_64(std::get<0>(unpacked), to.index());
				}

				noob::node_handle get_from() const noexcept(true)
				{
					return noob::node_handle::make(std::get<0>(noob::pack_64_to_32(val)));
				}

				noob::node_handle get_to() const noexcept(true)
				{
					return noob::node_handle::make(std::get<1>(noob::pack_64_to_32(val)));
				}

				bool operator<(const noob::digraph::edge rhs) const noexcept(true)
				{
					return val < rhs.val;
				}


				protected:
				uint64_t val;
			};

			static std::string to_string(const noob::digraph::edge e)
			{
				return noob::concat(noob::to_string(e.get_from().index()), "-", noob::to_string(e.get_to().index()));
			}

			// Does not affect the digraph - only reads from it. Therefore if you have a constant digraph, you can iterate over it from anywhere using these. :)
			// However, you MUST call is_valid prior to using it, and then has_child() prior to get_child(). Failure to do so will cause either garbage reads or segfaults.
			class visitor
			{
				friend class digraph;
				public:

				bool is_valid() const noexcept(true)
				{
					return (start_index != std::numeric_limits<uint32_t>::max());
				}

				bool has_child() const noexcept(true)
				{
					return (current_index < end_index);
				}

				noob::node_handle get_child() noexcept(true)
				{
					const noob::node_handle results = g.edges[current_index].get_to();
					++current_index;
					return results;
				}

				void reset() noexcept(true)
				{
					current_index = start_index;
				}

				protected:
				visitor(const noob::digraph& graph_arg, uint32_t start_arg, uint32_t end_arg) noexcept(true) : g(graph_arg), start_index(start_arg), end_index(end_arg), current_index(start_arg)  {}
				const noob::digraph& g;
				const uint32_t start_index, end_index;
				uint32_t current_index;
			};

			friend class visitor;

			uint32_t num_nodes() const noexcept(true)
			{
				return nodes.size();
			}

			uint32_t num_children(const noob::node_handle n) const noexcept(true)
			{
				return nodes[n.index()];
			}

			noob::node_handle add_node() noexcept(true)
			{
				nodes.push_back(0);
				return noob::node_handle::make(nodes.size() - 1);
			}

			// Grr, searching the hashtable mutates it! No const for you!
			bool edge_exists(const noob::node_handle first, const noob::node_handle second) noexcept(true)
			{
				auto search = edge_table.lookup(noob::pack_32_to_64(first.index(), second.index()));
				if (edge_table.is_valid(search))
				{
					return (search->value > 0);
				}
				return false;
			}

			void add_edge(const noob::node_handle first, const noob::node_handle second) noexcept(true)
			{
				if (!edge_exists(first, second))
				{
					noob::digraph::edge e;		
					e.set_from(first);
					e.set_to(second);
					edges.push_back(e);

					nodes[first.index()] += 1;

					auto search = edge_table.insert(noob::pack_32_to_64(first.index(), second.index()));
					search->value = std::numeric_limits<uint64_t>::max();

					ready = false;
				}
			}

			bool node_valid(const noob::node_handle n) const noexcept(true)
			{
				return !(n.index() > nodes.size());
			}

			bool is_ready() const noexcept(true)
			{
				return ready;
			}

			void sort() noexcept(true)
			{
				rde::quick_sort(edges.begin(), edges.end(), rde::less<noob::digraph::edge>());
				ready = true;
			}

			noob::digraph::visitor get_visitor(const noob::node_handle n) const noexcept(true)
			{
				const uint32_t num_children = nodes[n.index()];
				const uint32_t first_edge = get_first_edge_index(n);
				return noob::digraph::visitor(*this, first_edge, first_edge + num_children);
			}

			void clear() noexcept(true)
			{
				edge_table.clear();
				edges.clear();
				nodes.clear();
			}

			std::string to_string() const noexcept(true)
			{
				std::string results = noob::concat("Num nodes = ", noob::to_string(nodes.size()), ", num edges = ", noob::to_string(edges.size()), ". Edges: ");
				
				for (noob::digraph::edge e : edges)
				{	
					results = noob::concat(results, "", noob::to_string(e.get_from().index()), "-", noob::to_string(e.get_to().index()), ", ");
				}

				return results.substr(0, results.size() - 2);
			}


		protected:

			uint32_t get_first_edge_index(const noob::node_handle n) const noexcept(true)
			{
				noob::digraph::edge e;
				e.set_from(n);
				e.set_to(noob::node_handle::make(0));
				auto search = rde::lower_bound(edges.begin(), edges.end(), e , rde::less<noob::digraph::edge>());

				return (search - edges.begin());
			}


			noob::fast_hashtable edge_table;

			rde::vector<noob::digraph::edge> edges;
			rde::vector<uint32_t> nodes;

			bool ready;
	};
}
