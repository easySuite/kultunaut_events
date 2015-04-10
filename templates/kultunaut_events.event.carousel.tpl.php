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
    <div class="event-time">
      <div class="event-day"><?php echo $time; ?></div>
      <div class="event-date"><?php echo format_date($event_date, 'day_only'); ?></div>
      <div class="event-month"><?php echo format_date($event_date, 'short_month_only'); ?></div>
    </div>
    <div class="image">
      <a href="<?php echo $url; ?>"><?php echo $image; ?></a>
    </div>
    <div class="data">
      <div class="caption">
        <h3 style="height: 60px; max-height: 60px; overflow: hidden;"><?php echo $link;?></h3>
      </div>
    </div>
  </div>
</li>
