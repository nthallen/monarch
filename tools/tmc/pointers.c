/* pointers.c handles pointer sharing and proxy sharing.
 */
#include <stdio.h>
#include <strings.h>
#include "tmc.h"
#include "nl.h"

static struct ppp {
  struct ppp *next;
  char type;
  unsigned char id;
  char *name;
} *pps = NULL;
#define PPP_PTR 1
#define PPP_PROXY 2
#define PPP_RECV 4
static char ppp_has = 0;

void add_ptr_proxy(char *type, char *name, int id) {
  struct ppp *npp;
  char type_code;
  
  if (strcasecmp(type, "\"pointer\"") == 0) type_code = PPP_PTR;
  else if (strcasecmp(type, "\"proxy\"") == 0) type_code = PPP_PROXY;
  else if (strcasecmp(type, "\"receive\"") == 0) type_code = PPP_RECV;
  else
    compile_error(2, "Undefined type %s in pointer or proxy definition", type);

  if ( type_code == PPP_RECV ) {
    if ( id < 0 || id > 1 )
      compile_error(2, "TM 'Receive' ID (synch code) must be 0 or 1" );
  } else {
    for (npp = pps; npp != NULL; npp = npp->next)
        if (id == npp->id && type_code == npp->type)
          compile_error(2, "Duplicate ID %d in %s definition", id, type);
    if (id < 0 || id > 255)
      compile_error(2, "Illegal pointer or proxy ID %d", id);
  }
  npp = new_memory(sizeof(struct ppp));
  npp->next = pps;
  npp->id = id;
  npp->name = name;
  npp->type = type_code;
  ppp_has |= npp->type;
  pps = npp;
}

void print_recv_objs(void) {
  struct ppp *npp;
  if (ppp_has & PPP_RECV) {
    fprintf( ofile, "\n\n /* receive objects */\n" );
    for (npp = pps; npp != NULL; npp = npp->next)
      if (npp->type == PPP_RECV)
    fprintf(ofile, " TM_data_rcvr_def *%s_obj;\n", npp->name );
  }
}

static void print_pp_cases(void) {
  struct ppp *npp;

  if (ppp_has & PPP_PTR) {
    #ifdef PPP_PTR_IMPLEMENTED
      fprintf(ofile,
        "\tcase COL_SET_POINTER:\n"
        "\t  cmsg = (struct colmsg *)msg_ptr;\n"
        "\t  switch (cmsg->id) {\n");
      for (npp = pps; npp != NULL; npp = npp->next)
        if (npp->type == PPP_PTR) {
          fprintf(ofile,
            "\t\tcase %d: "
            "COL_get_pointer(sent_tid, &%s, cmsg->u.pointer); "
            "break;\n", npp->id, npp->name);
        }
      fprintf(ofile,
        "\t\tdefault: return(reply_byte(sent_tid, DAS_UNKN));\n"
        "\t  }\n"
        "\t  return(0);\n"
        "\tcase COL_RESET_POINTER:\n"
        "\t  cmsg = (struct colmsg *)msg_ptr;\n"
        "\t  switch (cmsg->id) {\n");
      for (npp = pps; npp != NULL; npp = npp->next)
        if (npp->type == PPP_PTR) {
          fprintf(ofile,
            "\t\tcase %d: "
            "COL_free_pointer(sent_tid, &%s); "
            "break;\n", npp->id, npp->name);
        }
      fprintf(ofile,
        "\t\tdefault: return(reply_byte(sent_tid, DAS_UNKN));\n"
        "\t  }\n"
        "\t  return(0);\n");
    #endif
  }
  if (ppp_has & PPP_PROXY) {
    #if PPP_PROXY_IMPLEMENTED
    fprintf(ofile,
      "\tcase COL_SET_PROXY:\n"
      "\t  cmsg = (struct colmsg *)msg_ptr;\n"
      "\t  switch (cmsg->id) {\n");
    for (npp = pps; npp != NULL; npp = npp->next)
      if (npp->type == PPP_PROXY) {
        fprintf(ofile,
          "\t\tcase %d: "
          "COL_recv_proxy(sent_tid, &%s, cmsg->u.proxy); "
          "break;\n", npp->id, npp->name);
      }
    fprintf(ofile,
      "\t\tdefault: return(reply_byte(sent_tid,DAS_UNKN));\n"
      "\t  }\n"
      "\t  return(0);\n"
      "\tcase COL_RESET_PROXY:\n"
      "\t  cmsg = (struct colmsg *)msg_ptr;\n"
      "\t  switch (cmsg->id) {\n");
      for (npp = pps; npp != NULL; npp = npp->next)
        if (npp->type == PPP_PROXY) {
            fprintf(ofile,
              "\t\tcase %d: "
              "COL_end_proxy(sent_tid, &%s, cmsg); "
              "break;\n", npp->id, npp->name);
          }
      fprintf(ofile,
        "\t\tdefault: return(reply_byte(sent_tid,DAS_UNKN));\n"
        "\t  }\n"
        "\t  return(0);\n");
    #endif
  }
  if (ppp_has & PPP_RECV) {
    for (npp = pps; npp != NULL; npp = npp->next)
      if (npp->type == PPP_RECV) {
    fprintf(ofile,
      "  %s_obj = receive(\"%s\", &%s, sizeof(%s), %d);\n",
      npp->name, npp->name, npp->name, npp->name, npp->id );
      }
  }
}

void print_ptr_proxy(void) {
  Skel_copy(ofile, "init_senders_head", 1);
  print_pp_cases();
  Skel_copy(ofile, "init_senders_tail", 1);
}

#ifdef __IMPLEMENTATION
Before DG_other
  #include "ofname"

In DG_other
  case COL_SET_POINTER:
    switch (cmsg->id) {
      case n: DG_get_pointer(sent_tid, &name, cmsg->u.ptr); break;
      default: return(reply_byte(DAS_UNKN));
    }
    return(0);
  case COL_RESET_POINTER:
    switch (cmsg->id) {
      case n: DG_free_pointer(send_tid, &name); break;
      default: return(reply_byte(DAS_UNKN));
    }
    return(0);
  case COL_SET_PROXY:
    switch (id) {
      case n: if (name != 0) return(DAS_UNKN); name = proxy; break;
      default: return DAS_UNKN;
    }
    break;
  case COL_RESET_PROXY:
    {
      pid_t proxy;
      
      switch (id) {
        case n: proxy = name; name = 0; break;
        default: return DAS_UNKN
      }
      return proxy;
    }
    break;
  case COL_SEND:
    cmsg = (struct colmsg *)msg_ptr;
    switch (cmsg->id) {
      case COL_SEND_INIT:
        if (strcasecmp(cmsg->u.name, "first") == 0) {
          cmsg->u.data.id = first.id;
          cmsg->u.data.size = first.size;
          cmsg->type = DAS_OK;
        } else if (strcasecmp...) {
        } else return reply_byte(sent_tid,DAS_UNKN);
        Reply(sent_tid, cmsg, offsetof(struct colmsg, u.data.data));
        return 0;
      case COL_SEND:
        switch (cmsg->u.data.id) {
          case n:
            memcpy(cmsg->u.data.data, structure, 
                    min(sizeof(structure), cmsg->u.data.size));
            break;
          default: return reply_byte(sent_tid, DAS_UNKN);
        }
        break;
      case COL_SEND_RESET: break;
      default: return reply_byte(sent_tid,DAS_UNKN);
    }
    return reply_byte(sent_tid, DAS_OK);
#endif
