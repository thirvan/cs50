$(document).ready(function() {
    $('.jQButton').click(function() {
        $('#colorDiv').css('background-color', this.innerHTML.toLowerCase());
    });
});