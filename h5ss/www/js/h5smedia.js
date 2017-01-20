
function H5SWebSocketClient(h5spath)
{
	var socket;
	try {
		//alert(window.location.protocol);
		if (window.location.protocol == "http:") 
		{
			socket = new WebSocket('ws://' + window.location.host + h5spath);
		}
		if (window.location.protocol == "https:")
		{	
			//alert(window.location.host);
			console.log(window.location.host);
			socket = new WebSocket('wss://' + window.location.host + h5spath);			 
		}
		console.log(window.location.host);
	} catch (e) {
		alert('error');
		return;
	}
	return socket;
}

window.onload = function() {
	var sourceBuffer;
	var buffer = [];	
	var mediaSource;
	var video;
	var wsSocket;

	var readFromBuffer = function () 
	{
		if (buffer.length === 0 || !sourceBuffer || sourceBuffer.updating) 
		{
		  return;
		}
		try {
		  var data = buffer.shift();
		  sourceBuffer.appendBuffer(data);
		} catch (e) {
		  console.log(e);
		}
	};
	
	function keepaliveTimer() 
	{
		wsSocket.send("keepalive");
	}

	function onWebSocketData(msg) 
	{
		var blob = msg.data;

		var fileReader = new FileReader();
		fileReader.onload = function () {
			buffer.push(this.result);
			readFromBuffer();
		};

		fileReader.readAsArrayBuffer(blob);
	}  
	
	window.MediaSource = window.MediaSource || window.WebKitMediaSource;
	if (!window.MediaSource) {
	  console.log('MediaSource API is not available');
	}

	mediaSource = new window.MediaSource();
	video = document.getElementById('h5sVideo');
	
	var h5spath = video.getAttribute('h5spath');

	/* var video = document.querySelector('h5sVideo'); */
	//alert(h5spath);
	video.src = window.URL.createObjectURL(mediaSource);

	mediaSource.addEventListener('sourceopen', function () {
		//var strCodec = 'video/mp4; codecs="avc1.420028"';
		//var strCodec = 'video/mp4; codecs="avc1.42E01E"';
		var strCodec = 'video/mp4; codecs="avc1.640029"';
		sourceBuffer = mediaSource.addSourceBuffer(strCodec);
		mediaSource.duration = Infinity;
		sourceBuffer.addEventListener('updateend', readFromBuffer);

	});

	video.addEventListener('play', function () {
		wsSocket = H5SWebSocketClient(h5spath);
		wsSocket.onmessage = onWebSocketData;
		setInterval(keepaliveTimer, 1000);	
	}, false);
	


}

