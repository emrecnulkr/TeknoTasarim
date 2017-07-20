jQuery(document).ready(function($) {
	var ticker = function()
	{
		setTimeout(function(){
			$("ul.ticker-list li:first").animate( {marginTop: '-30px'}, 800, function()
			{
				$(this).detach().appendTo("ul.ticker-list").removeAttr("style");	
			});
			ticker();
		}, 5000);
	};
	ticker();

});
