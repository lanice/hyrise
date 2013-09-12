$(document).ready( function() {
    $('body').addClass('onload');
     $('ul').each( function() {
        if (!$(this).hasClass('nav-pills')) {
            $(this).addClass('list notTop');
        }
    });
    $('ul.notTop li').addClass('list-group-item');
});