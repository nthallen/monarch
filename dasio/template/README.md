DAS_IO Templates

The templates in this directory are working applications with minimal functionality.
They can be used to test intercommunication in a variety of ways:

  - Run template_server1 in one window, template_client in another
    - Give both the -V option to show their output on screen
    - Or run memo first in anoother window
  - Run template_server1 by itself and then try to stop it with ctrl-C
    - While this works now, it should perform an orderly shutdown, and we
      should be able to see the difference
