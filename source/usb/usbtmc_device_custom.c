
#include "usbtmc_device_custom.h"
#include "device/usbd_pvt.h"

// TODO remove this USBTMC customisation once TinyUSB supports send srq
#if (CFG_TUD_USBTMC_ENABLE_488)
// I based this based on the PICO definition in tusb_config.h
#define PATCH_usbtmc_state_rhport (BOARD_TUD_RHPORT)
// I based this based on the PICO definition in usb_descriptors.c
#define PATCH_usbtmc_state_ep_int_in (0x82)
bool tud_usbtmc_send_srq(void) 
  {
    usbtmc_read_stb_rsp_488_t rsp;
    
    rsp.bTag = 0x01; //Indicates SRQ
    if (PATCH_usbtmc_state_ep_int_in != 0)  // see patch defines above
    {
      rsp.statusByte = 0x00; // Use interrupt endpoint, instead. Must be 0x00 (USB488v1.0 4.3.1.2)
      // if(usbd_edpt_busy(usbtmc_state.rhport, usbtmc_state.ep_int_in))
      if(usbd_edpt_busy(PATCH_usbtmc_state_rhport,PATCH_usbtmc_state_ep_int_in)) // see patch defines above
      {
        rsp.USBTMC_status = USB488_STATUS_INTERRUPT_IN_BUSY;
      }
      else
      {
        rsp.USBTMC_status = USBTMC_STATUS_SUCCESS;
        usbtmc_read_stb_interrupt_488_t intMsg =
        {
          .bNotify1 = {
              .one = 1,
              .bTag = 0x01 //Indicates SRQ
          },
          .StatusByte = tud_usbtmc_get_stb_cb(&(rsp.USBTMC_status))
        };
        // Must be queued before control request response sent (USB488v1.0 4.3.1.2)
        // usbd_edpt_xfer(usbtmc_state.rhport, usbtmc_state.ep_int_in, (void*)&intMsg, sizeof(intMsg));
        usbd_edpt_xfer(PATCH_usbtmc_state_rhport, PATCH_usbtmc_state_ep_int_in, (void*)&intMsg, sizeof(intMsg)); // see patch defines above
      }
    }
    else
    {
      rsp.statusByte = tud_usbtmc_get_stb_cb(&(rsp.USBTMC_status));
    }
    //TU_VERIFY(tud_control_xfer(usbtmc_state.rhport, request, (void*)&rsp, sizeof(rsp)));
    return true;
  }
#endif

