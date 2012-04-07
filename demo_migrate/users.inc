<?php

  class UserMigration extends Migration {

   public function __construct() {
    parent::__construct();
    $this->description = t('Migrate rails Users');

    $source_fields = array(
      'id' => t('User ID'),
    );

    $query = db_select('blog_demo_development.users', 'u')
              ->fields('u', array('id', 'username', 'email', 'crypted_password', 'created_at'))
              ->condition('u.username', array('admin'), "NOT IN");

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationUser();

    $this->map  = new MigrateSQLMap($this->machineName,
      array(
        'id' => array(
          'type'  => 'int',
          'unsigned'  => TRUE,
          'not null'  => TRUE,
          'description' => t('User id from old site'),
          'alias' => 'u',
          )
         ),
      MigrateDestinationUser::getKeySchema()
      );


    $this->addFieldMapping('name', 'username')->dedupe('users', 'name');
    $this->addFieldMapping('mail', 'email')->dedupe('users', 'mail');
    $this->addFieldMapping('pass', 'crypted_password');
    $this->addFieldMapping('language')->defaultValue('und');
    $this->addFieldMapping('theme')->defaultValue('');
    $this->addFieldMapping('signature')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('signature_format')->defaultValue('filtered_html');
    $this->addFieldMapping('created', time());
    $this->addFieldMapping('access')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('login')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('status')->defaultValue(1);
    $this->addFieldMapping('picture')->defaultValue(0);
    $this->addFieldMapping('init')
          ->issueGroup(t('DNM'));
  }

  public function complete($entity, stdClass $row) {
    $pass = 'U'.$entity->pass;
    $uid = $entity->uid;
    db_update('users')
      ->fields(array(
        'pass' => $pass,
      ))
      ->condition('uid', $uid)
      ->execute();
  }
}
