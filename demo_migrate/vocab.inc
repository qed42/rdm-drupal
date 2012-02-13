<?php

class vocabMigration extends Migration {
  public function __construct() {
    parent::__construct();

    $this->description = t("Migrate posts from rails 3 to drupal7");

    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'id' => array (
          'type' => 'integer',
          'length' => 10,
          'not null' => TRUE,
          'description' => 'term id from legacy table',
        )
      ),
      MigrateDestinationTerm::getKeySchema()
    );

    $query = db_select('blog_demo_development.categories', 'bddc')
              ->fields('bddc', array('id', 'name', 'created_at', 'updated_at'))
              ->orderBy('bddc.id', 'ASC');

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationTerm('category');

    $this->addFieldMapping('name', 'name');

    $this->addFieldMapping('description')
          ->issueGroup(t('DNM'));

    $this->addFieldMapping('parent_name', 0);

    $this->addFieldMapping('format')
           ->issueGroup(t('DNM'));

    $this->addFieldMapping('weight')
           ->issueGroup(t('DNM'));

    $this->addFieldMapping('parent')
           ->issueGroup(t('DNM'));

  }
}
