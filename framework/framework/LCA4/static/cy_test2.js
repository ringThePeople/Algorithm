$(function(){

    console.log('cy_test2.js has been called')
    graph_data = $('#graph-info2')[0].innerHTML.trim()
    var cy = window.cy = cytoscape({
        container: document.getElementById('cy2'),
        wheelSensitivity: 0.1,

boxSelectionEnabled: false,
autounselectify: true,
elements: [
        {
            group: 'node',
            position: {
                x: 200,
                y: 100
            }
        }
        ],
        layout: {
            name: 'circle'
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
                    'target-arrow-color': '#ccc',
                    'curve-style': 'bezier'
                }
            }
        ],

        elements: JSON.parse(graph_data),
    });

});