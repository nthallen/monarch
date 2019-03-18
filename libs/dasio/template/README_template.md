DAS_IO Templates {#templates}
================

The templates in this directory are working applications with minimal functionality.
They can be used to test intercommunication in a variety of ways:

  - Run template_server1 in one window, template_client in another
    - Give both the -V option to show their output on screen
    - Or run memo first in anoother window
  - Run template_server1 by itself and then try to stop it with ctrl-C
    - While this works now, it should perform an orderly shutdown, and we
      should be able to see the difference

Some guidelines to note with respect to writing server apps.

  - Each SubService requires a Serverside_client subclass and a socket_clone_t function that creates it.
    - You don't necessarily need a different subclass for each SubService.
  - Write the socket_clone_t function to match the prototype. Even though your function will return a pointer to the subclass, the return type should be Serverside_client *. That way you don't need to cast it when calling add_subserver(), and you are better assured that you have defined your class hierarchy correctly.