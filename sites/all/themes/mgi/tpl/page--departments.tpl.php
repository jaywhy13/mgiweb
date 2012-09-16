<?php include ('header.tpl.php');?>
	
	
	<div id="content"> 
		<?php print render($tabs);?>
		<?php print render($page['content'])?>
	</div>

<?php include ('footer.tpl.php');?>