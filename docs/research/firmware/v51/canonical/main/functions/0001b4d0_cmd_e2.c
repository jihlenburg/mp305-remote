/* Address: 0001b4d0; name: cmd_e2; body bytes: 328 */

/* WARNING: Removing unreachable block (ram,0x0001b52c) */

undefined4 cmd_e2(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  byte bVar3;
  int iVar4;
  undefined4 uVar5;
  char cVar6;
  
  *param_3 = *param_1 + '\x01';
  cVar6 = '\0';
  if (-1 < (int)((uint)(byte)DAT_1fff9550 << 0x1d)) {
    bVar1 = param_1[1];
    if ((bVar1 < 3) && (current_mode == '\x01')) {
      bVar3 = requested_mode;
      if (bVar1 != 1) goto LAB_0001b5be;
      if (remote_granted == '\x01') {
        cVar6 = '\0';
        bVar3 = param_1[4];
        remote_request = bVar1;
        if (bVar3 == 1) {
          bVar3 = param_1[2];
          if (3 < (byte)param_1[2]) {
            cVar6 = -1;
            bVar3 = DAT_1fffab18;
          }
          DAT_1fffab18 = bVar3;
          bVar2 = param_1[3];
          if (((cVar6 == '\0') && (bVar2 < 2)) && (DAT_1fffab17 != '\x01')) {
            if (bVar2 == 1) {
              if (((&DAT_1fffa3f4)[DAT_1fffa408] == '\0') ||
                 (iVar4 = get_output_faults(), iVar4 != 0)) goto LAB_0001b592;
              iVar4 = get_output_enabled();
              bVar3 = requested_mode;
              bVar1 = remote_request;
              if (iVar4 == 0) {
                DAT_1fffab18 = 0;
                DAT_1fffaad2 = 1;
                goto LAB_0001b5b8;
              }
            }
            else {
              bVar3 = requested_mode;
              if ((bVar2 == 0) &&
                 (iVar4 = get_output_enabled(), bVar3 = requested_mode, bVar1 = remote_request,
                 iVar4 == 1)) {
                DAT_1fffab18 = 0;
                FUN_0001aebc(0);
LAB_0001b5b8:
                FUN_0001cb8c(1);
                bVar3 = requested_mode;
                bVar1 = remote_request;
              }
            }
LAB_0001b5be:
            remote_request = bVar1;
            requested_mode = bVar3;
            cVar6 = '\0';
            control_dirty = 1;
            goto LAB_0001b5c2;
          }
        }
        else if (((bVar3 < 4) && (DAT_1fffab17 != '\x01')) &&
                (iVar4 = get_output_enabled(), bVar1 = remote_request, iVar4 == 0))
        goto LAB_0001b5be;
LAB_0001b592:
        cVar6 = -1;
      }
      else {
        cVar6 = '\x01';
      }
    }
    else {
      cVar6 = -1;
      if (bVar1 == 1) goto LAB_0001b592;
    }
  }
LAB_0001b5c2:
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
    else if (remote_granted != '\0') goto LAB_0001b5fa;
    if ((int)((uint)(byte)DAT_1fff9550 << 0x1d) < 0) {
      param_3[1] = '\x01';
      goto LAB_0001b602;
    }
  }
LAB_0001b5fa:
  param_3[1] = cVar6;
LAB_0001b602:
  uVar5 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar5 = 3;
  }
  return uVar5;
}

