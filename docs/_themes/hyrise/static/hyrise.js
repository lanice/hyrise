$(document).ready( function() {
    $('body').addClass('onload');
    $('ul').each( function() {
        if (!$(this).hasClass('topnav')) {
            $(this).addClass('list notTop');
        }
    });
    $('ul.notTop li').addClass('list-group-item');
    $('table').addClass('table');

    $('#learnmore').click(function() {
        $('html,body').stop().animate({scrollTop: $('#fullwidth').offset().top - $('#menu').height()}, 750);
    });
    $('.main .notTop').not('.simple').hide();
});