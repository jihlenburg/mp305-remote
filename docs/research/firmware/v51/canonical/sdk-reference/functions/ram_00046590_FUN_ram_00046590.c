/* Address: ram:00046590; name: FUN_ram_00046590; body bytes: 630 */

void FUN_ram_00046590(int param_1)

{
  byte bVar1;
  byte bVar2;
  char cVar3;
  int iVar4;
  undefined2 *puVar5;
  undefined2 *puVar6;
  byte bVar7;
  byte *pbVar8;
  
  gp = 0x20004000;
  if (param_1 == 0) {
    if (DAT_ram_20001a04 != (undefined1 *)0x0) {
      FUN_ram_000461a2();
      FUN_ram_0004588a(0);
      return;
    }
  }
  else if ((*(char *)(param_1 + 3) != '\0') &&
          (pbVar8 = *(byte **)(param_1 + 4), pbVar8 != (byte *)0x0)) {
    cVar3 = GAP_GetParamValue(0x16);
    for (bVar2 = 0; bVar2 < *(byte *)(param_1 + 3); bVar2 = bVar2 + 1) {
      if ((cVar3 <= (char)pbVar8[0xc]) && (DAT_ram_20001a04 != (undefined1 *)0x0)) {
        bVar1 = *pbVar8;
        if ((bVar1 & 0x10) == 0) {
          if ((bVar1 & 8) != 0) {
            bVar7 = 0xb;
            goto LAB_ram_000466c0;
          }
          if ((bVar1 & 1) == 0) {
            if ((bVar1 & 2) == 0) {
              if ((bVar1 & 4) == 0) {
                *pbVar8 = 7;
              }
              else {
                *pbVar8 = 10;
              }
            }
            else {
              if ((bVar1 & 4) != 0) {
                bVar7 = 9;
                goto LAB_ram_000466a8;
              }
              *pbVar8 = 6;
            }
          }
          else {
            if ((bVar1 & 4) == 0) {
              bVar7 = 8;
              goto LAB_ram_000466c0;
            }
            bVar7 = 5;
LAB_ram_000466a8:
            *pbVar8 = bVar7;
            pbVar8[0x17] = 0;
          }
        }
        else {
          if (bVar1 == 0x13) {
            *pbVar8 = 0;
            goto LAB_ram_00046630;
          }
          if ((bVar1 == 0x15) || (bVar1 == 0x1d)) {
            bVar7 = 1;
            goto LAB_ram_000466a8;
          }
          if (bVar1 == 0x12) {
            bVar7 = 2;
          }
          else if (bVar1 == 0x10) {
            bVar7 = 3;
          }
          else {
            if (bVar1 != 0x1b) goto LAB_ram_00046630;
            bVar7 = 4;
          }
LAB_ram_000466c0:
          *pbVar8 = bVar7;
        }
LAB_ram_00046630:
        iVar4 = FUN_ram_00045d6e(pbVar8);
        if (iVar4 != 0) {
          if (*pbVar8 < 5) {
            puVar5 = (undefined2 *)tmos_msg_allocate(pbVar8[0x17] + 0x14);
            if (puVar5 != (undefined2 *)0x0) {
              *puVar5 = 0xd0;
              *(undefined1 *)(puVar5 + 1) = 0xd;
              *(byte *)((int)puVar5 + 3) = *pbVar8;
              *(byte *)((int)puVar5 + 0xb) = pbVar8[0xc];
              *(byte *)(puVar5 + 2) = pbVar8[1];
              tmos_memcpy((int)puVar5 + 5,pbVar8 + 2,6);
              bVar1 = pbVar8[0x17];
              *(byte *)(puVar5 + 6) = bVar1;
              if (bVar1 == 0) {
                *(undefined4 *)(puVar5 + 8) = 0;
              }
              else {
                puVar6 = puVar5 + 10;
                *(undefined2 **)(puVar5 + 8) = puVar6;
LAB_ram_00046692:
                tmos_memcpy(puVar6,*(undefined4 *)(pbVar8 + 0x18));
              }
LAB_ram_0004671c:
              tmos_msg_send(*DAT_ram_20001a04,puVar5);
            }
          }
          else {
            puVar5 = (undefined2 *)tmos_msg_allocate(pbVar8[0x17] + 0x20);
            if (puVar5 != (undefined2 *)0x0) {
              *(undefined1 *)(puVar5 + 1) = 0x12;
              *puVar5 = 0xd0;
              *(byte *)((int)puVar5 + 3) = bVar1 & 0x60 | *pbVar8;
              *(byte *)(puVar5 + 2) = pbVar8[1];
              tmos_memcpy((int)puVar5 + 5,pbVar8 + 2,6);
              *(byte *)((int)puVar5 + 0xb) = pbVar8[8];
              *(byte *)(puVar5 + 6) = pbVar8[9];
              *(byte *)((int)puVar5 + 0xd) = pbVar8[10];
              *(byte *)(puVar5 + 7) = pbVar8[0xb];
              *(byte *)((int)puVar5 + 0xf) = pbVar8[0xc];
              puVar5[8] = *(undefined2 *)(pbVar8 + 0xe);
              *(byte *)(puVar5 + 9) = pbVar8[0x10];
              tmos_memcpy((int)puVar5 + 0x13,pbVar8 + 0x11,6);
              bVar1 = pbVar8[0x17];
              *(byte *)((int)puVar5 + 0x19) = bVar1;
              if (bVar1 != 0) {
                puVar6 = puVar5 + 0x10;
                *(undefined2 **)(puVar5 + 0xe) = puVar6;
                goto LAB_ram_00046692;
              }
              *(undefined4 *)(puVar5 + 0xe) = 0;
              goto LAB_ram_0004671c;
            }
          }
        }
      }
      pbVar8 = pbVar8 + 0x1c;
    }
  }
  return;
}

