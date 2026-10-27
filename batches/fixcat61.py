BS = chr(92)
for p in ('recomp.c', 'batches/tests61.c'):
    enc = 'utf-8-sig' if p == 'recomp.c' else 'utf-8'
    s = open(p, encoding=enc).read()
    old = '\tstrcpy(BUF + 0x300, "Data' + BS + BS + 'catalogue.dat");\n}'
    assert s.count(old) == 1, p
    new = ('\tstrcpy(BUF + 0x300, "Data' + BS + BS + 'catalogue.dat");\n'
           '\t/* a truncated file leaves a count as it was (fread reads nothing, the reader descrambles the old value):\n'
           '\t   small values there, as in the game, where they are the previous catalogue\'s */\n'
           '\tstatic const DWORD cnt[6] = { 0x13eb000, 0x140c8bc, 0x1447ec0, 0x148646c, 0x14d1ab0, 0x1561b64 };\n'
           '\tfor (int k = 0; k < 6; k++) S32(SCENE, cnt[k]) = irnd(0, 3);\n}')
    s = s.replace(old, new)
    open(p, 'w', encoding=enc).write(s)
print('ok')
