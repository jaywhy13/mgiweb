jQuery(document).ready(function($)
{
	$("#menu li.expanded").hover(function() {$("#menu li.expanded").nt-child(3).css('display','block')},function(){$("#menu li.expanded").nth-child(3).css('display','none')});
	$("#menu li.expanded .menu").mouseleave(function() {$("#menu li.expanded").children().css('display','none')});
});
										 