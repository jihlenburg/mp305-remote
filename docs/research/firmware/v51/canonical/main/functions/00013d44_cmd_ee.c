/* Address: 00013d44; name: cmd_ee; body bytes: 452 */

undefined4 cmd_ee(char *param_1,int param_2,char *param_3,int param_4)

{
  byte bVar1;
  byte bVar2;
  ushort uVar3;
  int iVar4;
  undefined4 uVar5;
  uint uVar6;
  char cVar7;
  
  *param_3 = *param_1 + '\x01';
  cVar7 = '\0';
  if (-1 < (int)((uint)(byte)DAT_1fff9550 << 0x1d)) {
    bVar1 = param_1[1];
    if ((bVar1 < 3) && (current_mode == 3)) {
      bVar2 = bVar1;
      if ((bVar1 == 1) && (remote_granted != '\x01')) {
        cVar7 = '\x01';
        goto LAB_00013eb2;
      }
    }
    else {
      cVar7 = -1;
      bVar2 = remote_request;
    }
    remote_request = bVar2;
    bVar2 = requested_mode;
    if (bVar1 == 1) {
      if (cVar7 == '\0') {
        if (remote_granted == '\0') {
LAB_00013eae:
          requested_mode = bVar2;
          DAT_1fffab19 = 1;
        }
        else {
          bVar2 = param_1[9];
          if (current_mode == bVar2) {
            if ((byte)param_1[2] < 6) {
              DAT_1fffac94._0_3_ = CONCAT12(param_1[2],(undefined2)DAT_1fffac94);
              cVar7 = '\0';
            }
            else {
              cVar7 = -1;
            }
            uVar3 = *(ushort *)(param_1 + 3);
            if (((cVar7 == '\0') &&
                (uVar6 = DAT_1fffac94 >> 0x10 & 0xff, (ushort)(&DAT_1ffe07e0)[uVar6 * 0xb] <= uVar3)
                ) && (uVar3 <= *(ushort *)(&DAT_1ffe07f4 + uVar6 * 0x16))) {
              DAT_1fffac94 = CONCAT22(DAT_1fffac94._2_2_,uVar3);
              cVar7 = '\0';
            }
            else {
              cVar7 = -1;
            }
            bVar1 = param_1[5];
            if ((((cVar7 == '\0') && ((bVar1 < 7 || (2 < DAT_1fffac94._2_1_)))) &&
                ((bVar1 < 9 || (3 < DAT_1fffac94._2_1_)))) &&
               ((bVar1 < 0xd || (4 < DAT_1fffac94._2_1_)))) {
              cVar7 = '\0';
              if (DAT_1fffac94._2_1_ != 5) {
                DAT_1fffac90 = CONCAT31(DAT_1fffac90._1_3_,bVar1);
              }
            }
            else {
              cVar7 = -1;
            }
            if ((cVar7 == '\0') && (*(ushort *)(param_1 + 6) < 0x1389)) {
              DAT_1fffac90 = CONCAT22(*(ushort *)(param_1 + 6),(undefined2)DAT_1fffac90);
              cVar7 = '\0';
            }
            else {
              cVar7 = -1;
            }
            bVar1 = param_1[8];
            if (((cVar7 == '\0') && (bVar1 < 2)) && (DAT_1fffab17 != '\x01')) {
              cVar7 = '\0';
              if (bVar1 == 1) {
                iVar4 = get_output_faults();
                if (iVar4 != 0) goto LAB_00013e7c;
                bVar2 = requested_mode;
                if ((DAT_1fffab47 == '\0') && (DAT_1fffab6a == 0)) {
                  FUN_0001d6fc(DAT_1fffac90,DAT_1fffac94);
                  DAT_1fffab44 = 0;
                  goto LAB_00013ea8;
                }
              }
              else {
                bVar2 = requested_mode;
                if ((bVar1 == 0) && (DAT_1fffab47 != '\0')) {
                  FUN_0001d858();
LAB_00013ea8:
                  FUN_0001cb8c(1);
                  bVar2 = requested_mode;
                }
              }
              goto LAB_00013eae;
            }
          }
          else if (((bVar2 < 4) && (DAT_1fffab17 != '\x01')) &&
                  (iVar4 = get_output_enabled(), iVar4 == 0)) goto LAB_00013eae;
LAB_00013e7c:
          cVar7 = -1;
        }
      }
    }
    else if (cVar7 == '\0') goto LAB_00013eae;
  }
LAB_00013eb2:
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
    else if (remote_granted != '\0') goto LAB_00013eea;
    if ((int)((uint)(byte)DAT_1fff9550 << 0x1d) < 0) {
      param_3[1] = '\x01';
      goto LAB_00013ef2;
    }
  }
LAB_00013eea:
  param_3[1] = cVar7;
LAB_00013ef2:
  uVar5 = 2;
  if (param_4 == 6) {
    param_3[2] = param_1[param_2 + -1];
    uVar5 = 3;
  }
  return uVar5;
}

