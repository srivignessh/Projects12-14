window.onload = function() 
{var myVar=setInterval(function(){myTimer()},1000);

function myTimer()
{

{
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
						 				
										 data=data.split("\n");
										 var j=data.length;
										 var d3= [];
										 for (var i = 0; i < j; i += 1) {
													var k=parseFloat(data[i])
													//if(k<1024& k>100 )
													//{ 
													//k=(k*3.6)/1024-1.8;
													d3.push([i,k] );
												//}
												}
										 $(function() 
										 {

												var d1 = [];
												var d2 =[];							
											    //console.log(d3)
												$.plot("#placeholder", [ d1,d2,d3]);

											});		

							
	}

}
}
