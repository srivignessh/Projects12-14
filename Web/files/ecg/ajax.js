$.ajax({
    url: "a.php",
    async: false,
    success: function (data2) {
      data=data2;
    
    },
    failure:function(data){
    	alert('Failure');
    }
  });	