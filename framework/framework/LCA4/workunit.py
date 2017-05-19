import json
import tools.hub as toolhub
from numpy import *
import csv

ERROR_CODE = ["", 1]

def is_valid_form(_data):
	return 0

def timeseriesanalysis(_tsdata):
	# expand with analysis tool
	# import other .py file
	return _tsdata

def tsv2json(_tsvdata):
	_line = _tsvdata.split('\n')
	graphdict = {'nodes':[], 'edges':[]}
	for eachnode in _line[0].strip().split(';'):
		graphdict['nodes'].append({'data':{'id':eachnode}})
	for eachline in _line[1:]:
		e1, e2 = eachline.strip().split('\t')
		graphdict['edges'].append({'data':{'source': e1, 'target': e2}})
	return json.dumps(graphdict)


def run(_tsdata, _options):
	if not _tsdata:
		return ERROR_CODE
	if is_valid_form(_tsdata):
		return ERROR_CODE

	table = [row.split('\t') for row in _tsdata.split('\n')]
	table = table[1:-1]

	#calculate length
	table_len = len(table[0]) - 1
	period_info = _options['period']
	

	_jsons = [None, None, None, None, None, None, None, None ]	
	sp = 1
	i = 0

	if period_info['type'] == 'at_once':
		_jsons[0] = tsv2json(toolhub.run(_tsdata, _options, 1, 1))
	elif period_info['type'] == 'available':
		period_val = int(period_info['value'])
		while (sp+((i+1) * period_val)-1 < table_len) :
			print "%d interation" , i+1 
			start_t = sp+ (i *period_val)
			end_t = sp+((i+1) * period_val)-1
			_2col = toolhub.run(_tsdata, _options, start_t, end_t)
			if _2col[0] == None:
				i = i+1
				continue
			_jsons[i] = tsv2json(_2col)
			i = i + 1 #
####			

#	_2col = toolhub.run(_tsdata, _options)
#	_2col2 = toolhub.run2(_tsdata, _options)
#	_2col3 = toolhub.run3(_tsdata, _options)
#
#	_json = tsv2json(_2col)
#	_json2 = tsv2json(_2col2)
#	_json3 = tsv2json(_2col3)

#	_jsons[0] = _json
#	_jsons[2] = _json2
#	_jsons[3]  = _json3

#	print "JSON: ", _jsons[1]
#	print "JSON: ", _jsons[2]
#	print "JSON: ", _jsons[3]


	return [_jsons, 0]

if __name__ == '__main__':
	print "SOMETHING HERE"