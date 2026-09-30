/* Address: 00014b14; name: FUN_00014b14; body bytes: 660 */

void FUN_00014b14(undefined4 param_1)

{
  byte bVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 uVar7;
  
  iVar2 = FUN_0004675a();
  iVar3 = FUN_00046688(param_1);
  bVar1 = DAT_1ffe0245 | DAT_1ffe0248 | DAT_1ffe0246;
  uVar4 = (uint)bVar1;
  if (uVar4 != 0) {
    return;
  }
  if ((iVar3 == 0xe) && (iVar5 = FUN_00046700(param_1), iVar5 != 0x1c)) {
    if (iVar2 == DAT_1ffe0348) {
      if ((remote_granted == '\0') || (DAT_1ffe0330 != 0)) {
        if ((DAT_1fffaadb == '\0') || (DAT_1ffe0330 != 0)) {
          if (DAT_1ffe0330 == DAT_1ffe0468) {
            FUN_0001814c();
            puVar6 = &DAT_1ffe0474;
LAB_00014c0c:
            FUN_00018114(*puVar6);
          }
          else if (DAT_1ffe0330 == DAT_1ffe068c) {
            FUN_00018060();
          }
          else if (DAT_1ffe0330 == DAT_1ffe06a0) {
            if (DAT_1fffab10 == '\0') {
              FUN_00017dec();
            }
          }
          else if (DAT_1ffe0330 == DAT_1ffe06b4) {
            FUN_0001794c();
          }
          else if (DAT_1ffe0330 == DAT_1ffe0478) {
            if ((DAT_1fffaadb == '\0') && (DAT_1fffaace == '\0')) {
              FUN_00017be4();
            }
          }
          else {
            if (DAT_1ffe0330 == DAT_1ffe0738) {
              FUN_0001814c();
              puVar6 = &DAT_1ffe0744;
              goto LAB_00014c0c;
            }
            if (DAT_1ffe0330 == DAT_1ffe075c) {
              FUN_00017bc0();
            }
            else {
              iVar5 = FUN_0004cd1e(DAT_1ffe0700);
              if (iVar5 == 0) {
                FUN_00017c5c();
              }
              else {
                iVar5 = FUN_0004cd1e(DAT_1ffe072c);
                if (iVar5 != 0) {
                  iVar5 = FUN_0004cd1e(DAT_1ffe05a8);
                  if (iVar5 == 0) {
                    FUN_00017ec4();
                  }
                  else if (DAT_1ffe034c == 0) {
                    if (DAT_1ffe05b8 == 0) {
                      if (((DAT_1ffe0620 != 0) && (iVar5 = FUN_0004cd1e(DAT_1ffe0680), iVar5 != 0))
                         && (iVar5 = FUN_0004cd1e(DAT_1ffe0654), iVar5 != 0)) {
                        FUN_00017a0c();
                      }
                    }
                    else {
                      iVar5 = FUN_0004cd1e();
                      if (((iVar5 == 0) && (iVar5 = FUN_0004cd1e(DAT_1ffe0614), iVar5 != 0)) &&
                         (iVar5 = FUN_0004cd1e(DAT_1ffe0608), iVar5 != 0)) {
                        FUN_00017f78();
                      }
                    }
                  }
                  else if (DAT_1ffe0330 == DAT_1ffe0450) {
                    FUN_00017e10();
                  }
                  else {
                    iVar5 = FUN_000527ec(DAT_1ffe0344);
                    if (((iVar5 != DAT_1ffe04f0) && (iVar5 = FUN_0004cd1e(DAT_1ffe04c8), iVar5 != 0)
                        ) && (iVar5 = FUN_0004cd1e(DAT_1ffe05a8), iVar5 != 0)) {
                      FUN_00018084();
                    }
                  }
                }
              }
            }
          }
          if (((DAT_1ffe0330 != DAT_1ffe0450) && (DAT_1ffe0330 != DAT_1ffe0700)) ||
             (DAT_1ffe0330 == 0)) {
            DAT_1ffe0243 = 1;
            DAT_1ffe02b0 = 0;
          }
        }
        else {
          FUN_0004e5a6(DAT_1ffe03bc,7,0);
          iVar2 = DAT_1ffe04bc;
        }
      }
      else {
        FUN_0004e5a6(DAT_1ffe03c4,7,0);
      }
      DAT_1ffe0245 = 1;
    }
    else if (DAT_1ffe0245 == 0) {
      if (iVar5 == 0x1d) {
        if (iVar2 == DAT_1ffe0354) {
          DAT_1fffab03 = 1;
          puVar6 = &DAT_1ffe035c;
        }
        else {
          if (iVar2 != DAT_1ffe0364) goto LAB_00014d64;
          DAT_1fffab04 = 1;
          puVar6 = &DAT_1ffe036c;
        }
        DAT_1ffe0245 = 1;
        FUN_0004e5a6(*puVar6,7,0);
        if (iVar2 == DAT_1ffe0348) {
          return;
        }
        goto LAB_00014d74;
      }
      if (iVar5 + -100 < 1) {
        if (DAT_1ffe023c != 0) {
          DAT_1ffe023c = bVar1;
          FUN_00047298(DAT_1ffe0144);
        }
      }
      else if (DAT_1ffe023c == 0) {
        DAT_1ffe023c = 1;
        FUN_000471d8(DAT_1ffe0144);
      }
    }
  }
LAB_00014d64:
  if (iVar2 != DAT_1ffe0348) {
    if (iVar3 == 0x10) {
      DAT_1ffe02b0 = uVar4;
      DAT_1ffe02b4 = uVar4;
      FUN_0004e91a(iVar2,2,4);
      uVar7 = FUN_0004037c(0xffa600);
      FUN_0004e8e6(iVar2,uVar7,4);
      return;
    }
    if (iVar3 == 0x11) {
LAB_00014d74:
      FUN_0004e91a(iVar2,0);
      return;
    }
  }
  return;
}

