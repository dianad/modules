<?php
// $Id: adsense_cse.results.inc,v 1.1.2.6 2009/03/31 14:41:01 jcnventura Exp $

/**
 * @file
 * Displays the page containing the results of the Adsense for Search box
 */

/**
 * Creates the CSE search results page for site-embedded search results
 *
 * @return
 *   JavaScript that embeds the Google results
 */
function _adsense_cse_results() {
  // Log the search keys:
  watchdog('AdSense search', 'Search keywords: '. urldecode(check_plain($_GET['as_q'])));

  // Output search results
  $width   = variable_get('adsense_cse_frame_width', ADSENSE_CSE_FRAME_WIDTH_DEFAULT);
  $country = variable_get('adsense_cse_country', ADSENSE_CSE_COUNTRY_DEFAULT);

  if (variable_get('adsense_test_mode', ADSENSE_TEST_MODE_DEFAULT)) {
    $output = _adsense_format_box("Results<br />width = ${width}<br />country = ${country}", $width, 100);
  }
  else {
    if (variable_get('adsense_secret_adtest', ADSENSE_SECRET_ADTEST_DEFAULT)) {
      $secret = '  var googleAdtest = "on";';
    }

    $output = <<<CSE_RESULTS_TXT
<div id="cse-search-results"></div>
<script type="text/javascript">
  var googleSearchIframeName = "cse-search-results";
  var googleSearchFormName = "cse-search-box";
  var googleSearchFrameWidth = $width;
  var googleSearchDomain = "$country";
  var googleSearchPath = "/cse";
$secret
</script>
<script type="text/javascript" src="http://www.google.com/afsonline/show_afs_search.js"></script>
CSE_RESULTS_TXT;

    // Remove empty lines
    $output = str_replace("\n\n", "\n", $output);
  }

  return $output;
}
