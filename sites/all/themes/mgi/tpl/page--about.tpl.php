<?php include ('header.tpl.php');?>
	
	
	 <div id="middle"  >
		<h2 class="pageTitle" ><?php print $title ?> </h2>
		<div id="leftColumn">
			<?php print render($page['leftColumn'])?>
		</div>
		<div id="rightColumn">
			<?php print render($page['rightColumn'])?>
		</div>
	</div>
	<div id="bios" > 
		<div id="hiddenBios">
			<?php print render($page['biosViewer'])?>
		</div>
		<div id="biosViewer">
		</div>
		<div id="biosScroller">
			<?php print render($page['biosScroller'])?>
		</div>
	</div>
	<div id = "about">
		<?php print render($page['about'])?>
	</div>		  
	<div id="associates">
		<?php print render($page['associates'])?>
	</div>			
   <div id="fellows">
		<?php print render($page['fellows'])?>
   </div>

	
<?php include ('footer.tpl.php');?>