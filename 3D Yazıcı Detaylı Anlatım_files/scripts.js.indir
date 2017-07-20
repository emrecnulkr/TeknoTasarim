jQuery(document).ready(function($) {

	// Mobi nav menu
	$(".flip").click(function(){
	$(".panel").slideToggle("fast");
  	});
  
	// Tabs

	//When page loads...
	$('.tabber-container').each(function() {
		$(this).find(".tabber-content").hide(); //Hide all content
		$(this).find("ul.tabs li:first").addClass("active").show(); //Activate first tab
		$(this).find(".tabber-content:first").show(); //Show first tab content
	});
	
	//On Click Event
	$("ul.tabs li").click(function(e) {
		$(this).parents('.tabber-container').find("ul.tabs li").removeClass("active"); //Remove any "active" class
		$(this).addClass("active"); //Add "active" class to selected tab
		$(this).parents('.tabber-container').find(".tabber-content").hide(); //Hide all tab content

		var activeTab = $(this).find("a").attr("href"); //Find the href attribute value to identify the active tab + content
		$(this).parents('.tabber-container').find(activeTab).fadeIn(); //Fade in the active ID content
		
		e.preventDefault();
	});
	
	$("ul.tabs li a").click(function(e) {
		e.preventDefault();
	})
	
	// Toggle
	$(".toggle-content").hide(); 

	$("h4.toggle").toggle(function(){
		$(this).addClass("active");
		}, function () {
		$(this).removeClass("active");
	});

	$("h4.toggle").click(function(){
		$(this).next(".toggle-content").slideToggle();
	});


});