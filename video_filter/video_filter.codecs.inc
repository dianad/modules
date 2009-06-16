<?php
// $Id: video_filter.codecs.inc,v 1.3.2.7 2009/03/29 20:09:53 blackdog Exp $

function video_filter_codec_info() {
  $codecs = array();

  $codecs['youtube'] = array(
    'name' => t('YouTube'),
    'callback' => 'video_filter_youtube',
    'regexp' => '/youtube\.com\/watch\?v=([a-z0-9\-_]+)/i',
    'ratio' => 425 / 355,
  );
  $codecs['google'] = array(
    'name' => t('Google Video'),
    'callback' => 'video_filter_google',
    'regexp' => '/video\.google\.com\/videoplay\?docid=(\-?[0-9]+)/',
    'ratio' => 400 / 326,
  );
  $codecs['tangle'] = array(
    'name' => t('Tangle'),
    'callback' => 'video_filter_tangle',
    'regexp' => '/tangle\.com\/view_video\.php\?viewkey=([a-z0-9]+)/',
    'ratio' => 330 / 270,
  );
  $codecs['dailymotion'] = array(
    'name' => t('DailyMotion'),
    'callback' => 'video_filter_dailymotion',
    'regexp' => '/dailymotion\.com\/.*video\/([a-z0-9]+)/i',
    'ratio' => 420 / 336,
  );
  $codecs['eyespot'] = array(
    'name' => t('Eyespot'),
    'callback' => 'video_filter_eyespot',
    'regexp' => '/eyespot\.com\/.*r=([a-z0-9]+)/i',
    'ratio' => 432 / 407,
  );
  $codecs['jumpcut'] = array(
    'name' => t('Jumpcut'),
    'callback' => 'video_filter_jumpcut',
    'regexp' => '/jumpcut\.com\/.*id=([A-Z0-9]+)/',
    'ratio' => 408 / 324,
  );
  $codecs['revver'] = array(
    'name' => t('Revver'),
    'callback' => 'video_filter_revver',
    'regexp' => '/revver\.com\/video\/([0-9]+)/',
    'ratio' => 408 / 324,
  );
  $codecs['vimeo'] = array(
    'name' => t('Vimeo'),
    'callback' => 'video_filter_vimeo',
    'regexp' => '/vimeo\.com\/([0-9]+)/',
    'ratio' => 400 / 225,
  );
  $codecs['flickr_slideshows'] = array(
    'name' => t('Flickr Slideshows'),
    'callback' => 'video_filter_flickr_slideshows',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/sets\/([0-9]+)\/?[show]?\/?/i',
    'ratio' => 400 / 300,
  );
  $codecs['flickr_video'] = array(
    'name' => t('Flickr Video'),
    'callback' => 'video_filter_flickr_video',
    'regexp' => '/flickr\.com\/photos\/([a-zA-Z0-9@_\-]+)\/([0-9]+)/',
    'ratio' => 400 / 226,
  );
  $codecs['gamevideos'] = array(
    'name' => t('Game Videos'),
    'callback' => 'video_filter_gamevideos',
    'regexp' => '/gamevideos\.1up\.com\/video\/id\/([0-9]+)/',
    'ratio' => 500 / 319,
  );
  $codecs['metacafe'] = array(
    'name' => t('Meta Cafe'),
    'callback' => 'video_filter_metacafe',
    'regexp' => '/metacafe\.com\/watch\/([a-z0-9\-_]+)\/([a-z0-9\-_]+)/i',
    'ratio' => 400 / 345,
  );
  $codecs['gametrailers'] = array(
    'name' => t('Game Trailers'),
    'callback' => 'video_filter_gametrailers',
    'regexp' => '/gametrailers\.com\/player\/([0-9]+)/',
    'ratio' => 480 / 392,
  );
  $codecs['collegehumor'] = array(
    'name' => t('College Humor'),
    'callback' => 'video_filter_collegehumor',
    'regexp' => '/collegehumor\.com\/video\:([0-9]+)/',
    'ratio' => 480 / 360,
  );
  $codecs['myspace'] = array(
    'name' => t('MySpace'),
    'callback' => 'video_filter_myspace',
    'regexp' => '/vids\.myspace\.com\/.*VideoID=([0-9]+)/i',
    'ratio' => 425 / 360,
  );

  return $codecs;
}

function video_filter_youtube($video) {
  $video['source'] = 'http://www.youtube.com/v/'.$video['codec']['matches'][1].($video['autoplay'] ? '&autoplay=1' : '').'&amp;fs=1';

  return video_filter_flash($video);
}

function video_filter_google($video) {
  $video['source'] = 'http://video.google.com/googleplayer.swf?docId='.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_tangle($video) {
  $video['source'] = 'http://www.tangle.com/flash/swf/flvplayer.swf?viewkey='.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_dailymotion($video) {
  $video['source'] = 'http://www.dailymotion.com/swf/'.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_eyespot($video) {
  $video['source'] = 'http://eyespot.com/flash/medialoader.swf?vurl=http%3A%2F%2Fdownloads.eyespot.com%2Fplay%3Fr%3D'.$video['codec']['matches'][1].'&_autoPlay='.($video['autoplay'] ? 'true' : 'false');

  return video_filter_flash($video);
}

function video_filter_jumpcut($video) {
  $video['source'] = 'http://jumpcut.com/media/flash/jump.swf?id='.$video['codec']['matches'][1].'&amp;asset_type=movie&amp;asset_id='.$video['codec']['matches'][1].'&amp;eb=1';

  return video_filter_flash($video);
}

function video_filter_revver($video) {
  $output = '<script src="http://flash.revver.com/player/1.0/player.js?mediaId:'.$video['codec']['matches'][1].';width:'.$video['width'].';height:'.$video['height'].';" type="text/javascript"></script>';

  return $output;
}

function video_filter_vimeo($video) {
  $video['source'] = 'http://www.vimeo.com/moogaloop.swf?clip_id='.$video['codec']['matches'][1].'&amp;server=www.vimeo.com&amp;fullscreen=1&amp;show_title=1&amp;show_byline=1&amp;show_portrait=0&amp;color=';

  return video_filter_flash($video);
}

function video_filter_flickr_slideshows($video) {
  $slideshow_player_url = 'http://www.flickr.com/apps/slideshow/show.swf?v=67348';
  $video['source'] = $slideshow_player_url . ($video['autoplay'] ? '&amp;autoplay=1' : '');

  $user_name = $video['codec']['matches'][1];
  $set_id = $video['codec']['matches'][2];

  $params['flashvars'] = "&amp;offsite=true&amp;lang=en-us&amp;page_show_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2Fshow%2F&amp;page_show_back_url=%2Fphotos%2F$user_name%2Fsets%2F$set_id%2F&amp;set_id=$set_id&amp;jump_to=";

  return video_filter_flash($video, $params);
}

function video_filter_flickr_video($video) {
  $video['source'] = 'http://www.flickr.com/apps/video/stewart.swf?v=1.161';

  $params['flashvars'] = '&amp;photo_id='.$video['codec']['matches'][2].'&amp;flickr_show_info_box=true';

  return video_filter_flash($video, $params);
}

function video_filter_gamevideos($video) {
  $video['source'] = 'http://gamevideos.1up.com/swf/gamevideos12.swf?embedded=1&amp;fullscreen=1&amp;autoplay=0&amp;src=http://gamevideos.1up.com/do/videoListXML%3Fid%3D'.$video['codec']['matches'][1];

  return video_filter_flash($video);
}

function video_filter_metacafe($video) {
  $video['source'] = 'http://metacafe.com/fplayer/'.$video['codec']['matches'][1].'/'.$video['codec']['matches'][2].'.swf';

  return video_filter_flash($video);
}

function video_filter_gametrailers($video) {
  $video['source'] = 'http://www.gametrailers.com/remote_wrap.php?mid='.$video['codec']['matches'][1];

  return video_filter_flash($video, $params);
}

function video_filter_collegehumor($video) {
  $video['source'] = 'http://www.collegehumor.com/moogaloop/moogaloop.swf?clip_id='.$video['codec']['matches'][1].'&amp;fullscreen=1';

  return video_filter_flash($video);
}

function video_filter_myspace($video) {
  $video['source'] = 'http://mediaservices.myspace.com/services/media/embed.aspx/m='.$video['codec']['matches'][1];

  return video_filter_flash($video, $params);
}