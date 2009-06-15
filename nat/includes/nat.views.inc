<?php
// $Id: nat.views.inc,v 1.2.2.3 2009/02/14 19:56:51 anantagati Exp $

function nat_views_data() {
  $data = array();

  $data['nat'] = array(
    'table' => array(
      'group' => t('NAT'), 
    ),
  );
  $data['nat']['table']['join']['node'] = array(
    'left_table' => 'term_node',
    'left_field' => 'tid',
    'field' => 'tid',
  );
  $data['nat']['nid'] = array(
    'title' => t('Nid'),
    'help' => t('The node ID of the NAT node.'),
    'field' => array(
      'handler' => 'views_handler_field_node',
      'click sortable' => TRUE,
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_node_nid',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'nid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  // Term to NAT node handling
  $data['tan'] = array(
    'table' => array(
      'group' => t('NAT'),
    ),
  );
  $data['tan']['table']['join']['node'] = array(
    'table' => 'nat',
    'left_field' => 'nid',
    'field' => 'nid',
  );
  $data['tan']['tid'] = array(
    'title' => t('Tid'),
    'help' => t('The tid of the NAT term.'),
    'argument' => array(
      'handler' => 'views_handler_argument_term_node_tid',
      'name field' => 'title',
      'numeric' => TRUE,
      'validate type' => 'tid',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
  );

  return $data;
}