import osmnx as ox 

ox.config(log_console=True, use_cache=True) 
graph = ox.graph_from_place("Manhattan, New York, New York, USA" ,network_type = 'drive')
fig, ax = ox.plot_graph(graph)

ox.save_load.save_graph_shapefile(graph, "Los_Angeles")