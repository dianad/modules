<?php
// $Id: xmlsitemap.cron.php,v 1.1.2.11 2009/05/25 22:41:55 kiam Exp $

/**
 * @file
 * Creates cache files using cron tasks.
 */

/**
 * The following path must be changed if the file is moved from the directory
 * currently containing it.
 */
include_once '../../../../../includes/bootstrap.inc';

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);

// Allow execution to continue even if the request gets canceled.
@ignore_user_abort(TRUE);

// Try to increase the maximum execution time if it is too low.
if (ini_get('max_execution_time') < 240) {
  @set_time_limit(240);
}

// Fetch the cron semaphore
$semaphore = variable_get('xmlsitemap_cron_semaphore', FALSE);

if ($semaphore) {
  if (REQUEST_TIME - $semaphore > 3600) {
    // Either the task has been running for more than an hour or the semaphore
    // was not reset due to a database error.
    watchdog('xmlsitemap', 'Cache files building task has been running for more than an hour and is most likely stuck.', array(), WATCHDOG_ERROR);
    
   // Release cron semaphore
    variable_del('xmlsitemap_cron_semaphore');
  }
  else {
    // The task is still running normally.
    watchdog('xmlsitemap', 'Attempting to re-run the cache files building task while it is already running.', array(), WATCHDOG_WARNING);
  }
}
else {
  // Register shutdown callback
  register_shutdown_function('_xmlsitemap_cron_cleanup');
  
  // Lock cron semaphore
  variable_set('xmlsitemap_cron_semaphore', REQUEST_TIME);
  
  // Update the information about the sitemap chunks.
  xmlsitemap_chunk_count(TRUE);
  
  // Build the cache files for the sitemap chunks.
  $chunks_info = variable_get('xmlsitemap_sitemap_chunks_info', array());
  $md5 = substr(md5($base_url), 0, 8);
  $parent_dir = variable_get('xmlsitemap_cache_directory', file_directory_path() .'/xmlsitemap');
  foreach($chunks_info as $module => $info) {
    $first_chunk = $info['first chunk'];
    // if first chunk is less than zero, the module is not enabled.
    if ($first_chunk < 0 || $info['chunks'] == 0) {
      continue;
    }
    
    if ($info['needs update']) {
      for ($chunk = $first_chunk; $chunk <= $first_chunk + $info['chunks'] - 1; $chunk++) {
        $chunk_size = variable_get('xmlsitemap_chunk_size', 1000);
        $delta = $chunk - $first_chunk;
        $from = $delta * $chunk_size;
        $count = min($info['links'] - $from, $chunk_size);
        $filename = $parent_dir .'/'. $md5 . $info['id'] . $delta . $language->language .'.xml';
        if ($fp = @fopen($filename, 'wb+')) {
          fwrite($fp, '<?xml version="1.0" encoding="UTF-8"?>'."\n");
          fwrite($fp, '<urlset xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">'."\n");
          module_invoke($module, 'xmlsitemap_links', $fp, $from, $count);
          fwrite($fp, '</urlset>');
          fclose($fp);
        }
      }
      $chunks_info[$module]['needs update'] = FALSE;
      variable_set('xmlsitemap_sitemap_chunks_info', $chunks_info);
    }
     
    // Release cron semaphore
    variable_del('xmlsitemap_cron_semaphore');
  }
}
