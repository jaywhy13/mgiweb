/*
 MIT License {@link http://creativecommons.org/licenses/MIT/}
*/
(function(m,n){var e,k;e=m.jQuery;k=e.ScrollTo=e.ScrollTo||{config:{duration:400,easing:"swing",callback:n,durationMode:"each",offsetTop:0,offsetLeft:0},configure:function(f){e.extend(k.config,f||{});return this},scroll:function(f,c){var a,b,d,g,i,h,l,j;a=f.pop();b=a.$container;d=b.get(0);g=a.$target;i=e("<span/>").css({position:"absolute",top:"0px",left:"0px"});h=b.css("position");b.css("position","relative");i.appendTo(b);a=i.offset().top;a=g.offset().top-a-parseInt(c.offsetTop,10);j=i.offset().left;
j=g.offset().left-j-parseInt(c.offsetLeft,10);g=d.scrollTop;d=d.scrollLeft;i.remove();b.css("position",h);i=function(a){0===f.length?"function"===typeof c.callback&&c.callback.apply(this,[a]):k.scroll(f,c);return!0};c.onlyIfOutside&&(h=g+b.height(),l=d+b.width(),g<a&&a<h&&(a=g),d<j&&j<l&&(j=d));h={};a!==g&&(h.scrollTop=a+"px");j!==d&&(h.scrollLeft=j+"px");h.scrollTop||h.scrollLeft?b.animate(h,c.duration,c.easing,i):i();return!0},fn:function(f){var c,a,b;c=[];var d=e(this);if(0===d.length)return this;
f=e.extend({},k.config,f);a=d.parent();for(b=a.get(0);1===a.length&&b!==document.body&&b!==document;){var g;g="visible"!==a.css("overflow-y")&&b.scrollHeight!==b.clientHeight;b="visible"!==a.css("overflow-x")&&b.scrollWidth!==b.clientWidth;if(g||b)c.push({$container:a,$target:d}),d=a;a=a.parent();b=a.get(0)}c.push({$container:e(e.browser.msie||e.browser.mozilla?"html":"body"),$target:d});"all"===f.durationMode&&(f.duration/=c.length);k.scroll(c,f);return this}};e.fn.ScrollTo=e.ScrollTo.fn})(window);

jQuery(document).ready(function() {
	var links = jQuery(".servicesMenu a");
	for(i=0; i<links.length; i++)
	{
		links[i].href = "javascript:scroll('"+i+"');";
	}
	
});

function scroll(index)
{
	jQuery(".service").eq(index).ScrollTo({
		duration:2000,
	});
}
