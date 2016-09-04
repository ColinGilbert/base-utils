#include <noob/graph/graph.hpp>
#include <noob/logger/logger.hpp>

#include <noob/strings/strings.hpp>

#include <cassert>
#include <iostream>

// #include <sstream>

namespace noob
{
	struct log_funct
	{
		static void log(noob::log_importance imp, const std::string& s)
		{
			std::cout << noob::concat(noob::to_string(imp), ": ", s, "\n");
		}
	};

	typedef logger_impl<log_funct> logger;
}



int main()
{
	noob::logger::log(noob::log_importance::INFO, noob::concat("Testing logger! ", noob::to_string(0.9998)));
	
	noob::digraph g;
	
	assert(g.num_nodes() == 0);
	
	const noob::node_handle a = g.add_node();
	const noob::node_handle b = g.add_node();
	const noob::node_handle c = g.add_node();
	

	assert(g.num_nodes() == 3);


	g.add_edge(a, b);

	assert(g.edge_exists(a, b) == true);
	assert(g.edge_exists(a, c) == false);
	assert(g.edge_exists(b, a) == false);
	assert(g.edge_exists(c, a) == false);

	g.add_edge(a, c);

	assert(g.edge_exists(a, b) == true);
	assert(g.edge_exists(a, c) == true);
	assert(g.edge_exists(b, a) == false);
	assert(g.edge_exists(c, a) == false);

	assert(g.num_children(a) == 2);
	assert(g.num_children(b) == 0);
	assert(g.num_children(c) == 0);


	rde::vector<noob::node_handle> pre_sort;
	
	noob::digraph::visitor v1 = g.get_visitor(a);
	assert(v1.is_valid() == true);
	while(v1.has_child())
	{
		pre_sort.push_back(v1.get_child());
	}

	assert(pre_sort.size() == 2);
	g.sort();

	rde::vector<noob::node_handle> post_sort;

	noob::digraph::visitor v2 = g.get_visitor(a);
	assert(v2.is_valid() == true);
	while(v2.has_child())
	{
		post_sort.push_back(v2.get_child());
	}
	
	assert(pre_sort.size() == post_sort.size());

	for (uint32_t i = 0; i < pre_sort.size(); ++i)
	{
		assert(pre_sort[i] == post_sort[i]);
	}

	

	noob::logger::log(noob::log_importance::INFO, "All pass! :)");
	
	return 0;
}
