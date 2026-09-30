/* Address: 0001b7f4; name: cmd_c8_dc_control; body bytes: 406 */

undefined4 cmd_c8_dc_control(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  int iVar3;
  undefined4 uVar4;
  char cVar5;
  
  *param_3 = *param_1 + '\x01';
  cVar5 = '\0';
  if (-1 < (int)((uint)(byte)DAT_1fff9550 << 0x1d)) {
    bVar1 = param_1[1];
    if ((bVar1 < 3) && (current_mode == 0)) {
      bVar2 = bVar1;
      if ((bVar1 == 1) && (remote_granted != '\x01')) {
        cVar5 = '\x01';
        goto LAB_0001b932;
      }
    }
    else {
      cVar5 = -1;
      bVar2 = remote_request;
    }
    remote_request = bVar2;
    bVar2 = requested_mode;
    if (bVar1 == 1) {
      if (cVar5 == '\0') {
        if (remote_granted != '\0') {
          bVar2 = param_1[10];
          if (current_mode == bVar2) {
            if (*(ushort *)(param_1 + 2) < 0xbeb) {
              set_voltage_raw();
              cVar5 = '\0';
            }
            else {
              cVar5 = -1;
            }
            if ((cVar5 == '\0') && (*(ushort *)(param_1 + 4) < 0x13ed)) {
              set_current_raw();
              cVar5 = '\0';
            }
            else {
              cVar5 = -1;
            }
            if ((cVar5 == '\0') && ((byte)param_1[6] < 4)) {
              cVar5 = '\0';
              DAT_1fffaae4 = param_1[6];
            }
            else {
              cVar5 = -1;
            }
            if ((cVar5 == '\0') && ((byte)param_1[7] < 2)) {
              cVar5 = '\0';
              DAT_1fffaadc = param_1[7];
            }
            else {
              cVar5 = -1;
            }
            if ((cVar5 == '\0') && ((byte)param_1[8] < 2)) {
              cVar5 = '\0';
              DAT_1fffaade = param_1[8];
            }
            else {
              cVar5 = -1;
            }
            bVar1 = param_1[9];
            if (((cVar5 == '\0') && (bVar1 < 2)) && (DAT_1fffab17 != '\x01')) {
              if (bVar1 == 1) {
                iVar3 = get_output_faults();
                if (iVar3 != 0) goto LAB_0001b8fa;
                iVar3 = get_output_enabled();
                if (iVar3 == 0) goto LAB_0001b90e;
              }
              else if ((bVar1 == 0) && (iVar3 = get_output_enabled(), iVar3 == 1)) {
LAB_0001b90e:
                FUN_0001cb8c(1);
              }
              FUN_0001aebc(bVar1);
              cVar5 = '\0';
            }
            else {
LAB_0001b8fa:
              cVar5 = -1;
            }
            if ((cVar5 != '\0') || (1 < (byte)param_1[0xb])) goto LAB_0001b922;
            cVar5 = '\0';
            bVar2 = requested_mode;
            if (param_1[0xb] == 1) {
              FUN_0001a5fc();
              bVar2 = requested_mode;
            }
          }
          else if (((3 < bVar2) || (DAT_1fffab17 == '\x01')) ||
                  (iVar3 = get_output_enabled(), iVar3 != 0)) {
LAB_0001b922:
            cVar5 = -1;
            goto LAB_0001b932;
          }
        }
LAB_0001b92e:
        requested_mode = bVar2;
        control_dirty = 1;
      }
    }
    else if (cVar5 == '\0') goto LAB_0001b92e;
  }
LAB_0001b932:
  if (remote_request == 2) {
    if (DAT_1fffaacf != '\x02') {
      return 0;
    }
    remote_request = 1;
    remote_granted = '\x01';
  }
  else {
    if (remote_request == 0) {
      remote_granted = '\0';
    }
    else if (remote_granted != '\0') goto LAB_0001b96c;
    if ((int)((uint)(byte)DAT_1fff9550 << 0x1d) < 0) {
      param_3[1] = '\x01';
      goto LAB_0001b974;
    }
  }
LAB_0001b96c:
  param_3[1] = cVar5;
LAB_0001b974:
  uVar4 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar4 = 3;
  }
  return uVar4;
}

