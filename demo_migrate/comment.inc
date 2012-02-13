<?php
class CommentMigration extends Migration {
  public function __construct() {
    parent::__construct();
    $this->description = 'Comments on posts';
    $this->map = new MigrateSQLMap($this->machineName,
      array('id' => array(
              'type' => 'int',
              'unsigned' => TRUE,
              'not null' => TRUE,
             )
           ),
        MigrateDestinationComment::getKeySchema()
      );
    $query = db_select('blog_demo_development.comments', 'c')
             ->fields('c', array('id','post_id','user_id','body', 'created_at', 'updated_at'))
                          ->orderBy('c.id');

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationComment('comment_node_posts');

    // Mapped fields
    $this->addFieldMapping('hostname')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('subject')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('mail')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('status')
         ->defaultValue(COMMENT_PUBLISHED);
    $this->addFieldMapping('nid', 'post_id')
         ->sourceMigration('post');
    $this->addFieldMapping('uid', 'user_id')
         ->sourceMigration('user')
         ->defaultValue(0);
    $this->addFieldMapping('pid')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('comment_body', 'body');

    $this->addFieldMapping('created', 'created_at');
    $this->addFieldMapping('changed', 'updated_at');
    $this->addFieldMapping('homepage')
          ->issueGroup(t('DNM'));
    $this->addFieldMapping('name')
          ->issueGroup(t('DNM'));

    // No unmapped source fields

    // Unmapped destination fields
    $this->addFieldMapping('thread')
         ->issueGroup(t('DNM'));
    $this->addFieldMapping('language')
         ->issueGroup(t('DNM'));
  }
}
?>
