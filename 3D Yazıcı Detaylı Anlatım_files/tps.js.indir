/*
 * Copyright 2012, Theia Post Slider, Liviu Cristian Mirea Ghiban.
 */
var tps = tps || {};
tps.slideshowsOnPage = 0;
tps.createSlideshow = function(options) {
	tps.slideshowsOnPage++;
    var me = this,
        $ = jQuery,
        defaults = {
            'src': '',
            'dest': '',
            'nav': [],
	        'navText': '%{currentSlide} of %{totalSlides}',
	        'defaultSlide': 0,
	        'transitionEffect': 'none',
	        'transitionSpeed': 400,
	        'keyboardShortcuts': false,
	        'slides': [],
	        'prevPost': null,
	        'nextPost': null
        };
    me.options = $.extend(defaults, options);
    me.srcE = $(me.options.src);
    me.destE = $(me.options.dest);
	if (me.destE.length == 0) {
		return;
	}
	me.navEl = [];
	for (var i = 0; i < me.options.nav.length; i++) {
		var e = $(me.options.nav[i]);
		if (e.length == 1) {
			me.navEl.push({
				container: e
			});
		}
	}

	// The current slide
    me.currentSlide = null;

	// The slide that is currently displayed. This may lag behind me.currentSlide because of the animations.
	me.currentlyDisplayedSlide = null;

	// The number of animations that are currently running.
	me.animations = 0;
	
	me.navEffect = tps.transitions[me.options.transitionEffect];

	// A queue that is executed when no animation is running.
	me.queue = [];

	// Initialization function
	me.init = function() {
	    // Get slides from me.options.slides
	    me.slides = [];
	    for (var i = 0; i < me.options.slides.length; i++) {
		    if (me.options.defaultSlide == i) {
		        //me.options.slides[i].content = me.srcE;
		    }
		    else {
			    var e = $('<div>');
			    e.html(me.options.slides[i].content);
			    me.options.slides[i].content = e;
		    }

	        me.slides[i] = me.options.slides[i];
	    }

		// Get slides from me.options.src element.
		var srcSlides = $(me.options.src);
		for (var i = 0; i < srcSlides.length; i++) {
			var s = $(srcSlides[i]);
			s.detach();
			var index = me.options.defaultSlide + i;
			me.slides[index] = me.slides[index] || {};
			me.slides[index].content = s;
		}

		// Count the slides.
		me.numberOfSlides = 0;
	    for (var i = 0; i < me.slides.length; i++) {
		    me.numberOfSlides++;
	    }

		// Setup the navigation bars.
		for (var i = 0; i < me.navEl.length; i++) {
			var navEl = me.navEl[i];
	        navEl.text = navEl.container.children('._text');
		    navEl.prev = navEl.container.children('._prev')
		        .click(function(that) {
		            return function() {
		                that.setPrev();
		                return false;
		            }
		        }(me));
		    navEl.next = navEl.container.children('._next')
		        .click(function(that) {
		            return function() {
		                that.setNext();
		                return false;
		            }
		        }(me));

			/*
			 Add _active class on mousedown. This is a fix for IE and Opera which don't match :active on container elements.
			 Also, return false to prevent double click context menu in Opera.
			*/
			navEl.container.children('._prev, ._next')
				.mousedown(function() {
					$(this).addClass('_active');
					return false;
				})
				.mouseup(function() {
					$(this).removeClass('_active');
				});
		}

		// Show the first slide
	    me.setSlide(me.options.defaultSlide);

		// Enable keyboard shortcuts
		if (me.options.keyboardShortcuts) {
			$(document).keydown(function(me) {
				return function(e) {
					// Disable shortcut if there is more than one slideshow on the page.
					if (tps.slideshowsOnPage > 1) {
						return;
					}

					// Disable shortcut if the target element is editable (input boxes, textareas, etc.).
					if (
                        this !== e.target &&
                        (
                            /textarea|select/i.test( e.target.nodeName ) ||
                            e.target.type === "text" ||
                            (
                                $(e.target).prop &&
                                $(e.target).prop('contenteditable') == 'true'
                            )
                        )
                    ) {
						return;
					}

					switch (e.which) {
						case 37:
							me.setPrev();
							return false;

						case 39:
							me.setNext();
							return false;
					}
				};
			}(me));
		}
	}

	// Enqueue a function to be executed when no animation is running.
	me.addToQueue = function(type, func) {
		me.queue.push({
			type: type,
			func: func
		});
		me.executeQueue();
	}

	// Execute the queue while there are no active animations.
	me.executeQueue = function() {
		while (me.animations == 0 && me.queue.length > 0) {
			var q = me.queue.pop();
			q.func(me);
		}
	}

	// Attach an animation (i.e. an animation has started). The queue won't be executed until the animations have all finished.
	me.attachAnimation = function() {
		me.animations++;
	}

	// Detach an animation (i.e. an animation has finished).
	me.detachAnimation = function() {
		me.animations--;
		me.executeQueue();
	}

	// Set the current slide.
	me.setSlide = function(index) {
		if (me.currentSlide == index) {
			return;
		}

		var previousSlide = me.currentSlide;
		me.currentSlide = index;

		// Scroll the window up, if the beginning of the slide is out-of-view.
		if (previousSlide != null) {
			// Get the lowest offset.top
			var scrollTop = me.destE.offset().top;
			for (var i in me.navEl) {
				scrollTop = Math.min(scrollTop, me.navEl[i].container.offset().top);
			}

			if ($(window).scrollTop() > scrollTop) {
				//$('body,html').scrollTop(scrollTop);
				$('body,html').animate({scrollTop: scrollTop}, me.options.transitionSpeed);
			}
		}

		// Set the navigation text.
		me.updateNavText();

	    // Update navigations bar.
		for (var i = 0; i < me.navEl.length; i++) {
			var navEl = me.navEl[i];

			// Disable or enable previous button
	        if (me.options.prevPost == null && me.currentSlide == 0) {
	           navEl.prev.addClass('_disabled');
	        }
	        else {
	            navEl.prev.removeClass('_disabled');
	        }

			// Disable or enable next button
	        if (me.options.nextPost == null && me.currentSlide == me.numberOfSlides - 1) {
	            navEl.next.addClass('_disabled');
	        }
	        else {
	            navEl.next.removeClass('_disabled');
	        }
		}

	    // Change URL, but only if this isn't the first slide set (i.e. the default slide).
		if (previousSlide != null) {
			var history = window.History;
		    if (history.enabled) {
			    var url = me.slides[me.currentSlide].permalink;

			    // Don't do anything if the slide doesn't have a permalink.
			    if (url) {
				    // TODO: move this somewhere else.
					history.Adapter.bind(window, 'statechange', function(me) {
				        return function() {
					        var state = History.getState();
							if (state.data.currentSlide != undefined) {
								me.setSlide(state.data.currentSlide);
							}
					        else {
								me.setSlide(me.options.defaultSlide);
							}
				        };
				    }(me));

				    history.pushState({
					    currentSlide: index
				    }, me.slides[me.currentSlide].title, url);
			    }
		    }
		}

		// Show the slide.
		me.enqueueShowSlide();
	}

	// Show (display) the current slide using the chosen animation.
    me.showSlide = function() {
	    // Don't do anything if the current slide is already shown.
	    if (me.currentlyDisplayedSlide == me.currentSlide) {
		    return;
	    }

	    // Track the pageview if this isn't the first slide displayed.
		if (me.currentlyDisplayedSlide != null && me.slides[me.currentSlide]['permalink']) {
			// URL Path
			var path = me.slides[me.currentSlide]['permalink'].split('/');
			if (path.length >= 4) {
				path = '/' + path.slice(3).join('/');

				// Google Analytics Async.
				if (typeof _gaq !== 'undefined' && typeof _gaq.push !== 'undefined') {
					_gaq.push(['_trackPageview', path]);
				}
				// Google Analytics Traditional (ga.js).
				if (typeof pageTracker !== 'undefined' && typeof pageTracker._trackPageview !== 'undefined') {
					pageTracker._trackPageview(path);
				}

				// Piwik
				if (typeof piwikTracker !== 'undefined' && typeof piwikTracker.trackPageView !== 'undefined') {
					piwikTracker.trackPageView(path);
				}
			}
		}

	    var previousIndex = me.currentlyDisplayedSlide;
	    me.currentlyDisplayedSlide = me.currentSlide;

	    // Change the slide while applying a certain effect/animation.
		me.navEffect(me, previousIndex, me.currentlyDisplayedSlide);
    }

	// Enqueue a showSlide call. See showSlide().
	me.enqueueShowSlide = function(index) {
		// If there is another showSlide call enqueued, then remove it.
		// This is useful in case the user clicks the back/next buttons very fast and the slider lags behind because of the animations.
		// Basically, this will skip the intermediary slides and display the last one.
		for (var i = 0; i < me.queue.length; i++) {
			if (me.queue[i].type == 'showSlide') {
				me.queue.splice(i, 1);
			}
		}

		me.addToQueue('showSlide', function(me) {
			me.showSlide();
		});
	}

	// Update the navigation bar's text.
	me.updateNavText = function() {
		for (var i = 0; i < me.navEl.length; i++) {
			var navEl = me.navEl[i];
			var navText = me.options.navText;
			navText = navText.replace('%{currentSlide}', me.currentSlide + 1);
			navText = navText.replace('%{totalSlides}', me.numberOfSlides);
	        navEl.text.html(navText);
		}
	}

	// Go to the previous slide.
    me.setPrev = function() {
        if (me.currentSlide == 0) {
	        if (me.options.prevPost) {
		        window.location = me.options.prevPost;
	        }
        }
	    else {
	        me.setSlide(me.currentSlide - 1);
        }
    }

	// Go to the next slide.
    me.setNext = function() {
        if (me.currentSlide == me.numberOfSlides - 1) {
	        if (me.options.nextPost) {
		        window.location = me.options.nextPost;
	        }
        }
	    else {
            me.setSlide(me.currentSlide + 1);
        }
    }

	// Set the transition properties.
	me.setTransition = function(options) {
		var defaults = {
			'effect': me.options.transitionEffect,
			'speed': me.options.transitionSpeed
		};
		options = $.extend(defaults, options);
		me.options.transitionEffect = options.effect;
		me.options.transitionSpeed = options.speed;
		me.navEffect = tps.transitions[me.options.transitionEffect];
	}

	// Set the navigation bar's text template.
	me.setNavText = function(navText) {
		me.options.navText = navText;
		me.updateNavText();
	}

	// Initialize the slider.
	me.init();
};