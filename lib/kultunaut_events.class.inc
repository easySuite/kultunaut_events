<?php
/**
 * @file
 * KultunautEvent class definition.
 */

/**
 * Class KultunautEvent.
 */
class KultunautEvent {
  protected $place;
  protected $date;
  protected $startDate;
  protected $endDate;
  protected $time;
  protected $title;
  protected $description;
  protected $category;
  protected $image;
  protected $url;
  protected $downloadHandler;
  protected $savedImage;

  /**
   * Load data from SimpleXMLElement object.
   *
   * @param SimpleXMLElement $xml
   *   Event "tag" returned from server.
   */
  public function fromSimpleXMLElement(SimpleXMLElement $xml) {
    // Local setters to XML tags mapping.
    $map = array(
      'setPlace' => 'sted',
      'setDate' => 'dato',
      'setStartDate' => 'startdato',
      'setEndDate' => 'slutdato',
      'setTime' => 'tid',
      'setTitle' => 'overskrift',
      'setDescription' => 'beskrivelse',
      'setCategory' => 'kategori',
      'setImage' => 'billede',
      'setUrl' => 'url',
    );

    foreach ($map as $setter => $tag) {
      $this->$setter((string) $xml->$tag);
    }

    $this->downloadImage();
  }

  /**
   * Set place.
   *
   * @param string $value
   *   Place of the event.
   */
  public function setPlace($value) {
    $this->place = $value;
  }

  /**
   * Set date.
   *
   * @param string $value
   *   Date text.
   */
  public function setDate($value) {
    $this->date = $value;
  }

  /**
   * Set start date.
   *
   * @param string $value
   *   Start date of the event.
   */
  public function setStartDate($value) {
    $tmp = new DateTime($value);
    $this->startDate = $tmp->getTimestamp();
  }

  /**
   * Set end date.
   *
   * @param string $value
   *   End date of the event.
   */
  public function setEndDate($value) {
    $tmp = new DateTime($value);
    $this->endDate = $tmp->getTimestamp();
  }

  /**
   * Set time.
   *
   * @param string $value
   *   Time text.
   */
  public function setTime($value) {
    $this->time = $value;
  }

  /**
   * Set title.
   *
   * @param string $value
   *   Event name.
   */
  public function setTitle($value) {
    $this->title = $value;
  }

  /**
   * Set description.
   *
   * @param string $value
   *   Event description.
   */
  public function setDescription($value) {
    $this->description = $value;
  }

  /**
   * Set category.
   *
   * @param string $value
   *   Event category.
   */
  public function setCategory($value) {
    $this->category = $value;
  }

  /**
   * Set original image URL.
   *
   * @param string $value
   *   Original image URL.
   */
  public function setImage($value) {
    $this->image = $value;
  }

  /**
   * Set URL.
   *
   * @param string $value
   *   Event page URL.
   */
  public function setUrl($value) {
    $this->url = $value;
  }

  /**
   * Get URL.
   *
   * @return string
   *   Event page URL.
   */
  public function getUrl() {
    return $this->url;
  }

  /**
   * Get description.
   *
   * @return string
   *   Event description.
   */
  public function getDescription() {
    return $this->description;
  }

  /**
   * Get category.
   *
   * @return string
   *   Event category.
   */
  public function getCategory() {
    return $this->category;
  }

  /**
   * Get image array suitable for theming.
   *
   * @return array
   *   Theming array.
   */
  public function getImageArray() {
    $result = array(
      'path' => $this->savedImage,
      'alt' => $this->getTitle(),
      'title' => $this->getTitle(),
    );
    return $result;
  }

  /**
   * Get start date.
   *
   * @return int
   *   Start date timestamp.
   */
  public function getStartDate() {
    return $this->startDate;
  }

  /**
   * Get title.
   *
   * @return string
   *   Event name.
   */
  public function getTitle() {
    return $this->title;
  }

  /**
   * Get time.
   *
   * @return string
   *   Event time text.
   */
  public function getTime() {
    return $this->time;
  }

  /**
   * Set download handler function.
   *
   * @param callable $handler
   *   Function for downloading images.
   */
  public function setImageDownloadHandler($handler) {
    $this->downloadHandler = $handler;
  }

  /**
   * Download original image to local storage.
   */
  public function downloadImage() {
    $this->savedImage = call_user_func($this->downloadHandler, $this->image);
  }
}
