(function ($) {

	var SCROLL_OFFSET = 60;
	var SCROLL_DURATION = 100;

	$(document).ready(function () {

		$(window).on('hashchange', function(event) {

			var params = (event.originalEvent.newURL||'').split('#');
			var page = params[0];
			var anchor = params[1];

			// if link on same page, animate
			if (window.location.href.split('#')[0] === page) {			
				var target = $('#' + anchor);

				$('body, html').animate({
				    scrollTop: (target[0] && target.offset().top || 0) - SCROLL_OFFSET
				}, SCROLL_DURATION);
			}

		});

		var $body = $('body');
		var $menu = $('.hyrisesidebar');
		var $list = $menu.find('.localtoc ul:first');

		/**
		 * set the height of the sidebar according to the height of the window
		 * @return {[type]} [description]
		 */
		var handleWindowResize = function() {

			var top = $('.navbar').height();
			var scroll = $('.inner-wrapper .upper').height()// - $(window).scrollTop();

			var height = Math.min(scroll, $(window).height()) - top - 25;

			$menu.height(height);
			// $menu.affix(();
		};

		var handleLocalTocClick = function(event) {
			// use custom scrollTo function instead of default implementation
			event.preventDefault();

			var target = event.target;
			target = $($(target).attr('href'));

			$('body, html').animate({
			    scrollTop: (target[0] && target.offset().top || 0) - SCROLL_OFFSET
			}, SCROLL_DURATION);
		};

		var initFooter = function() {
			$menu.affix({
				offset: {
					bottom	: function() {
						return $('.footer_toc').outerHeight(true) + $('.footer').outerHeight(true) + 45;	
					}
				}
			})

		};

		$menu.find('ul li:not(:has(ul))').addClass('leaf');

		$list.find('a').click(handleLocalTocClick);

		if (location.pathname.match(/\/documentation/)) {
			$body[0].setAttribute('data-spy', 'scroll');
			$body[0].setAttribute('data-target', '.hyrisesidebar');
			
			// init scroll spy
			$body.scrollspy({
				offset: 61
			});
		}

		var doit;
		$(window).resize(function(){
		  clearTimeout(doit);
		  doit = setTimeout(handleWindowResize, 100);
		});

		initFooter();
		handleWindowResize();

	});

}($jqTheme || window.jQuery));