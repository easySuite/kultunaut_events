<?php
/**
 * @file
 * Kultunaut event template for ding_nodelist.
 *
 * Avaialable variables:
 *   $item - KultunautEvent object.
 */
$image = $item->getImageArray();
$category = $item->getCategory();
$event_date = $item->getStartDate();
$time = $item->getTime();
$url = $item->getUrl();
$title = $item->getTitle();

$link = l($title, $url);
$image = $image ? theme(
  'image_style',
  array_merge($image, array('style_name' => $conf['image_style']))
) : '';
?>
<li class="event item">
  <div class="item_content">
    <div class="expand"><?php echo $link; ?></div>
    <div class="label"><?php echo t('Calendar');?></div>
    <div class="event-date">
      <div class="event-day"><?php echo format_date($event_date, 'day_only'); ?></div>
      <div class="event-month"><?php echo format_date($event_date, 'short_month_only'); ?></div>
    </div>
    <div class="image">
      <a href="<?php echo $url; ?>"><?php echo $image; ?></a>
    </div>
    <div class="data">
      <div class="caption">
        <h3><?php echo $link;?></h3>
      </div>
      <div class="library">
        <div class="event-time">
          <span><?php echo t('Time');?></span>
          <span><?php echo $time; ?></span>
        </div>
      </div>
    </div>
  </div>
</li>
