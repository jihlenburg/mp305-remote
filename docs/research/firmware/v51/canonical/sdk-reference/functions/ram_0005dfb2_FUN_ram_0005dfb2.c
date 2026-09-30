/* Address: ram:0005dfb2; name: FUN_ram_0005dfb2; body bytes: 300 */

void FUN_ram_0005dfb2(int param_1)

{
  undefined1 uVar1;
  int iVar2;
  
  gp = 0x20004000;
  *(undefined1 *)(param_1 + 0xc) = 0xc;
  **(undefined1 **)(param_1 + 0x74) = 3;
  *(byte *)(*(int *)(param_1 + 0x74) + 1) = *(byte *)(param_1 + 0xc) & 0x3f;
  *(undefined1 *)(param_1 + 0x4c) = 0;
  if ((*(byte *)(param_1 + 0x4d) & 2) == 0) {
LAB_ram_0005e024:
    if ((*(byte *)(param_1 + 0x54) & 2) != 0) {
LAB_ram_0005dfee:
      if (*(char *)(*(int *)(param_1 + 100) + 0x12) != '\0') {
        tmos_memcpy(*(int *)(param_1 + 0x74) + 8,*(int *)(param_1 + 100) + 0x14,6);
      }
    }
    if ((*(byte *)(param_1 + 0x4c) & 2) != 0) goto LAB_ram_0005e046;
  }
  else if ((*(byte *)(param_1 + 0x54) & 2) != 0) {
    iVar2 = *(int *)(param_1 + 100);
    if ((iVar2 != 0) && (*(char *)(iVar2 + 10) != '\0')) {
      *(undefined1 *)(param_1 + 0x4c) = 2;
      tmos_memcpy(*(int *)(param_1 + 0x74) + 2,iVar2 + 0xc,6);
      goto LAB_ram_0005e024;
    }
    goto LAB_ram_0005dfee;
  }
  tmos_memcpy(*(int *)(param_1 + 0x74) + 2,param_1 + 0x4e,6);
LAB_ram_0005e046:
  if (*(char *)(param_1 + 0x54) != '\x03') {
    tmos_memcpy(*(int *)(param_1 + 0x74) + 8,param_1 + 0x56,6);
  }
  if (((*(byte *)(param_1 + 0x4d) & 1) != 0) || (*(char *)(param_1 + 0x4c) == '\x02')) {
    **(byte **)(param_1 + 0x74) = **(byte **)(param_1 + 0x74) | 0x40;
  }
  if (((*(byte *)(param_1 + 0x55) & 1) != 0) || (*(char *)(param_1 + 0x54) == '\x03')) {
    **(byte **)(param_1 + 0x74) = **(byte **)(param_1 + 0x74) | 0x80;
  }
  if (*(char *)(param_1 + 0xd) == '\a') {
    uVar1 = *(undefined1 *)(param_1 + 0x25);
    *(undefined1 *)(param_1 + 10) = 0xa6;
  }
  else {
    *(undefined1 *)(param_1 + 10) = 0xa2;
    uVar1 = 2;
    if (*(char *)(param_1 + 0x21) != '\x02') {
      uVar1 = 0;
    }
  }
  FUN_ram_00061f0a(uVar1,*(undefined1 *)(param_1 + 0xc));
  return;
}

