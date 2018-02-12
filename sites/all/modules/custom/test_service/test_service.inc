<?php
// test_service.inc
/**
* Callback for creating test services.
*
* @param object $data
* @return object
*/
function _test_service_create($subject, $test) {
  global $user;
 
  // unset($data->id);
  // $data->uid = $user->uid;
  // $data->created = time();
  // $data->modified = time();
  // $data->subject = $subject;
  // $data->test = $test;

  $data = array(
    "uid" => $user->uid,
    "created" => time(),
    "modified" => time(),
    "subject" => $subject,
    "test" => $test
  );
 
  if (!isset($subject)) {
    return services_error('Missing test attribute subject', 406);
  }
 
  if (!isset($test)) {
    return services_error('Missing test attribute test', 406);
  }
 
  $insert = test_service_write_test($data);
   
  // return (object)array(
  //   'id' => $data->id,
  //   'uri' => services_service_uri(array('test', $data->id)),
  // );

  return array("Insert Success!");
}
 
// test_service.inc
/**
* Callback for updating test services.
*
* @param int $id
* @param object $data
* @return object
*/
function _test_service_update($id, $subject, $test) {
  global $user;
  // $test = test_service_get_test($id);
 
  // unset($data->created);
  // $data->id = $id;
  // $data->uid = $test->uid;
  // $data->modified = time();
 
  // test_service_write_test($data);
   
  // return (object)array(
  //   'id' => $id,
  //   'uri' => services_service_uri(array('test', $id)),
  // );

  $data = array(
    "id" => $id,
    "modified" => time(),
    "subject" => $subject,
    "test" => $test
  );
 
  if (!isset($subject)) {
    return services_error('Missing test attribute subject', 406);
  }
 
  if (!isset($test)) {
    return services_error('Missing test attribute test', 406);
  }
 
  $update = test_service_update_test($data);
   
  // return (object)array(
  //   'id' => $data->id,
  //   'uri' => services_service_uri(array('test', $data->id)),
  // );

  return array("Update Success!");
} 
/**
* Callback for retrieving test services.
*
* @param int $id
* @return object
*/
function _test_service_retrieve($id) {
  return test_service_get_test($id);
}
 
/**
* Callback for deleting test services.
*
* @param int $id
* @return object
*/
function _test_service_delete($id) {
  test_service_delete_test($id);
   
  return (object)array(
    'id' => $id,
  );
}
 
function _test_service_index($page, $parameters) {
  global $user;
 
  $tests = array();
  $res = db_query("SELECT * FROM {test} 
                WHERE uid='".$user->uid."'ORDER BY modified DESC");
  foreach ($res as $test) {
    $tests[] = $test;
  }
 
  return $tests;
}
 
/**
* Access callback for the test service.
*
* @param string $op
*  The operation that's going to be performed.
* @param array $args
*  The arguments that will be passed to the callback.
* @return bool
*  Whether access is given or not.
*/
 
function _test_service_access($op, $args) {
  global $user;
  $access = FALSE;
 
  switch ($op) {
    case 'view':
      $test = test_service_get_test($args[0]);
      $access = user_access('test service view any test');
      $access = $access || $test->uid == $user->uid && 
      user_access('test service view own tests');
      break;
    case 'update':
      $test = test_service_get_test($args[0]->id);
      $access = user_access('test service edit any test');
      $access = $access || $test->uid == $user->uid &&  
      user_access('test service edit own tests');
      break;
    case 'delete':
      $test = test_service_get_test($args[0]);
      $access = user_access('test service delete any test');
      $access = $access || $test->uid == $user->uid && 
      user_access('test service delete own tests');
      break;
  }
  $access = TRUE;
   
  return $access;
}
?>