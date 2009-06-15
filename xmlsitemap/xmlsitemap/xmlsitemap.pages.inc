<?php
// $Id: xmlsitemap.pages.inc,v 1.1.2.28 2009/05/24 11:08:08 kiam Exp $

/**
 * @file
 * XML sitemap page callbacks.
 */

/**
 * @addtogroup xmlsitemap
 * @{
 */

/*****************************************************************************
 * Menu callbacks / form builders, submit/validate functions.
 ****************************************************************************/

/**
 * Menu callback; display the sitemap .
 * @param $chunk
 *  An integer specifying which chunk of the sitemap is being requested.
 *  If not set and there is more than one chunk, display the sitemap index.
 */
function xmlsitemap_output_chunk($chunk) {
  if (!is_numeric($chunk)) {
    drupal_not_found();
    exit();
  }
  $chunks = xmlsitemap_chunk_count();
  if ($chunk < 0 || $chunk > $chunks) {
    drupal_not_found();
    exit();
  }
  $headers = array("Content-type: text/xml; charset=utf-8");
  $file = xmlsitemap_cache_filename($chunk);
  // If the cache file doesn't exist, try to get the first 100 links directly
  // from the database tables.
  if (($fp = @fopen($file, 'rb')) === FALSE) {
    _xmlsitemap_output_chunk_links($chunk);
    exit();
  }
  else {
    fclose($fp);
    file_transfer($file, $headers);
    exit();
  }
}

/**
 * Menu callback; display the sitemap index.
 */
function xmlsitemap_output_index() {
  $chunks = xmlsitemap_chunk_count();
  if ($chunks != variable_get('xmlsitemap_previous_chunk_count', -1)) {
    if (!variable_get('menu_rebuild_needed', FALSE)) {
      variable_set('menu_rebuild_needed', TRUE);
    }
    variable_set('xmlsitemap_previous_chunk_count', $chunks);
  }
  print <<< EOL
<?xml version="1.0" encoding="UTF-8"?>
<sitemapindex xmlns="http://www.sitemaps.org/schemas/sitemap/0.9">

EOL;
  for ($chunk = 0; $chunk < $chunks; ++$chunk) {
    $url = url("sitemap-$chunk.xml", array('absolute' => TRUE));
    print <<<EOL
  <sitemap>
    <loc>$url</loc>
  </sitemap>

EOL;
  }
  print '</sitemapindex>';
}

/*****************************************************************************
 * Private functions.
 ****************************************************************************/

function _xmlsitemap_output_chunk_links($chunk) {
  $chunks_info = variable_get('xmlsitemap_sitemap_chunks_info', array());
  print <<<EOL
<?xml version="1.0" encoding="UTF-8"?>
<urlset xmlns='http://www.sitemaps.org/schemas/sitemap/0.9'>

EOL;
  foreach ($chunks_info as $module => $info) {
    $first_chunk = $info['first chunk'];
    if ($chunk >= $first_chunk && $chunk <= $first_chunk + $info['chunks'] - 1) {
      $count = variable_get('xmlsitemap_chunk_size', 1000);
      $from = ($chunk - $first_chunk) * $count;
      module_invoke($module, 'xmlsitemap_links', 0, $from, $count);
      break;
    }
  }
  print '</urlset>';
}

/**
 * @} End of "addtogroup xmlsitemap".
 */
