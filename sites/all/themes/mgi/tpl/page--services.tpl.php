<?php include ('header.tpl.php');?>
	<div id="deptSlider">
		  <?php print render($page['slider'])?>
	</div>
    <div id="leftColumn">
         <?php print render($page['leftColumn'])?>
	</div>
	   <div id="rightColumn">
         <?php print render($page['rightColumn'])?>
	</div>
     <div id='bottomHalf'>       
	<div id="content" style="clear:both;"> 
		<?php print render($page['deptSummaries'])?>
	</div>
	</div>
	
	
 
<?php include ('footer.tpl.php');?>

