# Steps to Install:
* clone these modules into site/all/modules/custom folder of your drupal instance.
* Enable feature_migrate_demo (Requires features module) -- this will setup all required content types for the migration process to work with.
* Enable migrate module followed with migrate_demo module.

#Steps for migration:
* Using drush:
  * drush ms -- lists all the migration classes.
  * drush mi <classs name> -- migrates all the contents specific to a class.
    * arguments--
      * idlist -- migrates a single unique row from legacy system to the new system
          e.g., <pre><code>drush mi post --idlist=1</pre></code>
      * limit -- limits migration process upto a number of rows.
        e.g., <pre><code>drush mi post --limit="10 items"</pre></code>
      * feedback -- shows status after migrating n items or after n secs.
        e.g., <pre><code>drush mi post --feedback="10 items"</pre></code>
  * drush mr <class name> -- rolls back the imported data.<br />

--for more info use drush help.

* Using migrate_ui:
  * Go to content->migrate which shows up a list of migration classes with a few statistics and operations as a dropdown list.
  * Select the migration class and the operations and click go.   
