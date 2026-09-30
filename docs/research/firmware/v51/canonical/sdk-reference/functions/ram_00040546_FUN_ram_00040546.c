/* Address: ram:00040546; name: FUN_ram_00040546; body bytes: 298 */

void FUN_ram_00040546(void)

{
  undefined1 *puVar1;
  uint uVar2;
  int iVar3;
  uint uVar4;
  undefined1 *puVar5;
  undefined1 *puVar6;
  
  gp = 0x20004000;
  if (DAT_ram_20001bb8 != (undefined1 *)0x0) {
    puVar5 = (undefined1 *)0x0;
    puVar1 = DAT_ram_20001bb8;
    do {
      if (*(short *)(puVar1 + 2) == 0) {
        puVar6 = *(undefined1 **)(puVar1 + 0xc);
        if (puVar5 != (undefined1 *)0x0) {
          *(undefined1 **)(puVar5 + 0xc) = *(undefined1 **)(puVar1 + 0xc);
          puVar6 = DAT_ram_20001bb8;
        }
LAB_ram_00040598:
        DAT_ram_20001bb8 = puVar6;
        puVar6 = *(undefined1 **)(puVar1 + 0xc);
        FUN_ram_00040374(puVar1);
      }
      else {
        uVar2 = (*DAT_ram_20001c00)();
        uVar4 = *(uint *)(puVar1 + 8);
        if ((DAT_ram_20001bd2 < '\0') || (uVar4 <= uVar2)) {
          iVar3 = -uVar4;
        }
        else {
          iVar3 = -0x57400000 - uVar4;
        }
        if (uVar2 + iVar3 < 30000000) {
          DAT_ram_20001b74 = 0;
          (*(code *)&SUB_ram_e00823a8)(*puVar1,*(undefined2 *)(puVar1 + 2));
          puVar6 = *(undefined1 **)(puVar1 + 0xc);
          if (*(int *)(puVar1 + 4) == 0) {
            if (puVar5 != (undefined1 *)0x0) {
              *(undefined1 **)(puVar5 + 0xc) = puVar6;
              puVar6 = DAT_ram_20001bb8;
            }
            goto LAB_ram_00040598;
          }
          uVar2 = *(int *)(puVar1 + 4) + *(int *)(puVar1 + 8);
          if ((-1 < DAT_ram_20001bd2) && (0xa8bfffff < uVar2)) {
            uVar2 = uVar2 + 0x57400000;
          }
          *(uint *)(puVar1 + 8) = uVar2;
          puVar5 = puVar1;
        }
        else {
          if (DAT_ram_20001be0 != 0) {
            if ((-1 < DAT_ram_20001bd2) && (uVar4 < uVar2)) {
              uVar4 = uVar4 + 0xa8c00000;
            }
            if (uVar4 - uVar2 < DAT_ram_20001b74) {
              DAT_ram_20001b74 = uVar4 - uVar2;
            }
          }
          puVar6 = *(undefined1 **)(puVar1 + 0xc);
          puVar5 = puVar1;
        }
      }
      puVar1 = puVar6;
    } while (puVar6 != (undefined1 *)0x0);
    if (DAT_ram_20001b74 < 3) {
      DAT_ram_20001b74 = 0;
    }
    else {
      DAT_ram_20001b74 = DAT_ram_20001b74 - 2;
    }
  }
  return;
}

