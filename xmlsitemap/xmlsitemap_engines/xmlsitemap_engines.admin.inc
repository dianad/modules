<?php
// $Id: xmlsitemap_engines.admin.inc,v 1.1.2.9 2009/05/23 14:08:18 kiam Exp $

/**
 * @file
 * XML sitemap engines settings UI.
 */

/**
 * @addtogroup xmlsitemap
 * @{
 */

/*****************************************************************************
 * Menu callbacks / form builders, submit/validate functions.
 ****************************************************************************/

/**
 * Form builder; return the search engine settings form.
 */
function xmlsitemap_engines_settings() {
  $form['submission'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submission settings'),
    '#collapsible' => TRUE,
  );
  $form['submission']['xmlsitemap_engines_submit'] = array(
    '#type' => 'checkbox',
    '#title' => t('Submit the sitemap on content updates'),
    '#description' => t('If enabled, search engines will be notified of changes to the sitemap each time the site content is updated.'),
    '#default_value' => variable_get('xmlsitemap_engines_submit', FALSE),
  );
  $form['submission']['xmlsitemap_engines_cron_submit_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Frequency of sitemap submission'),
    '#description' => t('The rate at which the sitemap is submitted to the search engines.'),
    '#default_value' => variable_get('xmlsitemap_engines_cron_submit_frequency', 3600),
    '#options' => array(
      '29030400' => t('Yearly'),
      '14515200' => t('Every 6 months'),
      '2419200' => t('Monthly'),
      '1296000' => t('Every 15 days'),
      '604800' => t('Weekly'),
      '86400' => t('Daily'),
      '3600' => t('Hourly'),
      '-1' => t('Never'),
    ),
  );
  $form['submission']['submission_urls'] = array(
    '#type' => 'fieldset',
    '#title' => t('Submission URLs'),
    '#description' => t('Use %placeholder instead of the sitemap URL. Select the checkbox to enable the submission for a specific search engine.', array('%placeholder' => '[sitemap]')),
    '#collapsible' => TRUE,
  );
  foreach (_xmlsitemap_engines_get_engines_data() as $id => $info) {
    $form['submission']['submission_urls'][$id]['inline'] = array(
      '#prefix' => '<div class="container-inline">',
      '#suffix' => '</div>'
    );
    $form['submission']['submission_urls'][$id]['inline']["xmlsitemap_engines_{$id}_submit"] = array(
      '#type' => 'checkbox',
      '#title' => '',
      '#default_value' => variable_get("xmlsitemap_engines_{$id}_submit", FALSE),
    );
    $form['submission']['submission_urls'][$id]['inline']["xmlsitemap_engines_{$id}_url"] = array(
      '#type' => 'textfield',
      '#title' => '',
      '#default_value' => variable_get("xmlsitemap_engines_{$id}_url", $info[1]),
      '#size' => 40,
      '#field_suffix' => '<span class="description">'. $info[0] .'</span>',
    );
  }
  $form['verification'] = array(
    '#type' => 'fieldset',
    '#title' => t('Verification settings'),
    '#collapsible' => TRUE,
  );
  $form['verification']['google']['xmlsitemap_engines_google_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Google verification link'),
    '#description' => t('In order to show statistics, Google will ask you to verify that you control this site by creating a file with a certain name. Enter that name here and the XML sitemap module will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_google_verify', ''),
  );
  $form['verification']['live']['xmlsitemap_engines_live_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Windows Live authentication file'),
    '#description' => t('Before allowing you to view additional information, Windows Live will ask you to verify that you control this site by creating a file with a certain name. Enter that name here, and XML sitemap will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_live_verify', 'LiveSearchSiteAuth.xml'),
  );
  $form['verification']['live']['xmlsitemap_engines_live_verify_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Windows Live authentication tag'),
    '#description' => t('Windows Live will give you an authentication tag.'),
    '#default_value' => variable_get('xmlsitemap_engines_live_verify_string', ''),
  );
  $form['verification']['yahoo']['xmlsitemap_engines_yahoo_verify'] = array(
    '#type' => 'textfield',
    '#title' => t('Yahoo! verification link'),
    '#description' => t('Before allowing you to view additional information, Yahoo! will ask you to verify that you control this site by creating a file with a certain name. Enter that name here, and XML sitemap will create a path to that file name. This will only work if you have clean URLs enabled.'),
    '#default_value' => variable_get('xmlsitemap_engines_yahoo_verify', ''),
  );
  $form['verification']['yahoo']['xmlsitemap_engines_yahoo_verify_string'] = array(
    '#type' => 'textfield',
    '#title' => t('Yahoo! authentication key'),
    '#description' => t('Yahoo! will ask you to put an authentication key in the verification file.'),
    '#default_value' => variable_get('xmlsitemap_engines_yahoo_verify_string', ''),
  );
  $form = system_settings_form($form);
  $form['#submit'][] = 'xmlsitemap_engines_settings_submit';
  return $form;
}

/**
 * Submit the settings form.
 */
function xmlsitemap_engines_settings_submit($form, &$form_state) {
  variable_set('menu_rebuild_needed', TRUE);
}

/**
 * @} End of "addtogroup xmlsitemap".
 */
