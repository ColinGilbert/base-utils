// Near minimal as naive_graphs get.
#pragma once

#include <cstdint>
#include <limits>
#include <assert.h>

#include <algorithm>
#include <vector>

#include <noob/component/component.hpp>
#include <noob/bitpack/bitpack.hpp>

#include <rdestl/sort.h>

namespace noob
{
	typedef noob::handle<uint32_t> node_handle;

	class graph
	{
		public:
			// Does not affect the graph - only reads from it. Therefore if you have a constant graph, you can iterate over it from anywhere.
			// However, you MUST use has_next() - which is extremely cheap - prior to calling get_next() or else you'll either get garbage or a segfault.
			class visitor
			{
				friend class graph;
				public:

				bool has_next() const noexcept(true)
				{
				}

				noob::node_handle get_next() noexcept(true)
				{
				}

				void reset() noexcept(true)
				{
				}

				protected:
			};

			friend class visitor;


			uint32_t num_nodes() const noexcept(true)
			{
			}

			noob::node_handle add_node() noexcept(true)
			{
			}

			void add_child(const noob::node_handle first, const noob::node_handle second) noexcept(true)
			{
			}

			bool node_valid(const noob::node_handle n) const noexcept(true)
			{
			}

			bool graph_valid() const noexcept(true)
			{
			}

			noob::graph::visitor get_visitor(const noob::node_handle n) const noexcept(true)
			{
			}

			void clear() noexcept(true)
			{
			}

			void empty() noexcept(true)
			{
			}

			void reserve(uint32_t num) noexcept(true)
			{
			}

		protected:
			static constexpr uint32_t invalid_32 = std::numeric_limits<uint32_t>::max();
			static constexpr uint64_t invalid_64 = std::numeric_limits<uint64_t>::max();

	};
}
