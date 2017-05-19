import pandas as pd
import numpy as np
import genie3
import repack

def run(_data, _options, sp, ep):
	tool_name = _options['tool']
	period_info = _options['period']
	res_adj = []

	if period_info['type'] == 'at_once':
		adj = genie3.run_GENIE3(_data)		
		twocol = repack.adj2twocol(adj)
		return twocol
		print "whole data will be analyzed"
	elif period_info['type'] == 'available':
		adj = genie3.run_GENIE3(_data, sp, ep)
		if (adj[0] is None):
			return [None, None]
		twocol = repack.adj2twocol(adj)
		return twocol

		print "multiple analysis are on process"

def run2(_data, _options):
	tool_name = _options['tool']
	period_info = _options['period']
	res_adj = []

	if period_info['type'] == 'at_once':
		adj = genie3.run_GENIE3(_data)
		twocol = repack.adj2twocol(adj)
		return twocol
		print "whole data will be analyzed"
	elif period_info['type'] == 'available':
		adj = genie3.run_GENIE3(_data, 2, 6)
		twocol = repack.adj2twocol(adj)
		return twocol

		print "multiple analysis are on process"

def run3(_data, _options):
	tool_name = _options['tool']
	period_info = _options['period']
	res_adj = []

	if period_info['type'] == 'at_once':
		adj = genie3.run_GENIE3(_data)
		twocol = repack.adj2twocol(adj)
		return twocol
		print "whole data will be analyzed"
	elif period_info['type'] == 'available':
		adj = genie3.run_GENIE3(_data, 3, 7)
		twocol = repack.adj2twocol(adj)
		return twocol

		print "multiple analysis are on process"