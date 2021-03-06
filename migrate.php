<?$modules = module_list(TRUE);
db_set_active('mysql');
foreach ($modules as $module) {
    drupal_install_schema($module);
}

db_set_active('default');
foreach ($modules as $module) {
    $schema = drupal_get_schema_unprocessed($module);
    _drupal_schema_initialize($module, $schema);
   foreach ($schema as $table => $info) {
       db_set_active('default');
       $rows = db_query("SELECT * FROM {$table}");
       db_set_active('mysql');
       foreach ($rows as $row) {
           if (!isset($count) || ($count > 50)) {
                if (isset($insert)) {
                    $insert->execute();
                }
               $insert = db_insert($table);
               $count = 0;
           }
           $insert->fields((array) $row);
           $count++;
       }
       $insert->execute();
   }
}?>
