/* Address: 00012690; name: build_bind_reply; body bytes: 36 */

/* Builds 19 00 or 19 ff from device state +0x46; adds zero route byte for type 6. */

undefined4 build_bind_reply(undefined1 *param_1,int param_2)

{
  undefined4 uVar1;
  
  *param_1 = 0x19;
  if (bind_decision == '\0') {
    param_1[1] = 0xff;
  }
  else {
    param_1[1] = 0;
  }
  uVar1 = 2;
  if (param_2 == 6) {
    param_1[2] = 0;
    uVar1 = 3;
  }
  return uVar1;
}

