$(function(){

    graph_data = $('#graph-info')[0].innerHTML.trim()
    var cy = window.cy = cytoscape({
        container: document.getElementById('cy'),
        wheelSensitivity: 0.1,

boxSelectionEnabled: false,
autounselectify: true,
        elements: [
        {
            group: 'node',
            position: {
                x: 100,
                y: 100
            }
        }
        ],
        layout: {
         name: 'breadthfirst',
 fit: true,
idealEdgeLength: 100,
        nodeOverlap: 20


        },

        style: [
            {
                selector: 'node',
                style: {
                    'content': 'data(id)',
                    'text-opacity': 0.5,
                    'text-valign': 'center',
                    'text-halign': 'left',
                    'background-color': '#11479e'
                }
            },

            {
                selector: 'edge',
                style: {
                    'width': 4,
                    'target-arrow-shape': 'triangle',
                    'line-color': '#9dbaea',
                    'target-arrow-color': '#9dbaea',
                    'curve-style': 'bezier'
                }
            }
        ],

        elements: JSON.parse(graph_data)
    });

}

);