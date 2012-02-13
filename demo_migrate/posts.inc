<?php

class postMigration extends Migration {
  public function __construct() {
    parent::__construct();

    $this->descriprion = t("Migrate posts from rails to drupal7");

    $source_fields = array(
      'nid' => t('Node ID'),
    );

    $query = db_select('blog_demo_development.posts','p')
             ->fields('p', array('id', 'user_id', 'title', 'body', 'created_at', 'updated_at', 'category_id'));

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationNode('posts');

    $this->map = new MigrateSQLMap($this->machineName,
        array(
          'id' => array('type' => 'int',
                          'unsigned' => TRUE,
                          'not null' => TRUE,
                          'description' => t('Node id from old site'),
                          'alias' => 'p',
                         )
        ),
        MigrateDestinationNode::getKeySchema()
    );


    $this->addFieldMapping('is_new')->defaultValue(TRUE);
    $this->addFieldMapping('title', 'title');
		$this->addFieldMapping('uid', 'user_id')
    		 ->sourceMigration('user')
    		 ->defaultValue(1);
    $this->addFieldMapping('status')->defaultValue(TRUE);
    $this->addFieldMapping('revision_uid')
				->issueGroup(t('DNM'));
		$this->addFieldMapping('revision')
				->issueGroup(t('DNM'));
    $this->addFieldMapping('created', 'created_at');
    $this->addFieldMapping('changed', 'updated_at');
    $this->addFieldMapping('comment')->defaultValue(2);
    $this->addFieldMapping('promote')->defaultValue(1);
    $this->addFieldMapping('sticky')->defaultValue(0);
    $this->addFieldMapping('language')
    		->defaultValue('und');
    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('path')
    			->issueGroup(t('DNM'));

    $this->addFieldMapping('field_category', 'category_id')
         ->sourceMigration('vocab')
         ->arguments(array('source_type' => 'tid'));
  }
}
