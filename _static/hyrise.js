$(document).ready( function() {
    $('body').addClass('onload');
    $('ul').each( function() {
        if (!$(this).hasClass('topnav') && !$(this).hasClass('search')) {
            $(this).addClass('list notTop');
        }
    });
    $('ul.notTop li').addClass('list-group-item');
    $('table').addClass('table');

    $('#learnmore').click(function() {
        $('html,body').stop().animate({scrollTop: $('#fullwidth').offset().top - $('#menu').height()}, 750);
    });
    $('.main .notTop').not('.simple').hide();

    $(window).scroll(function() {
        var scrollTop = $(this).scrollTop();
        
        if (scrollTop > 100) {
             $('#backToTop').fadeIn({duration:100});
        } else {
             $('#backToTop').hide();
        }
    });

    $('#backToTop').click(function() {
        $('html,body').stop().animate({scrollTop: 0}, 750);
    }).hide();
});