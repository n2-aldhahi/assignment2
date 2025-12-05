echo ""
echo "=========================================="
echo "ASSIGNMENT 2: Minimal OS"
echo "=========================================="


echo "Building kernel..."
make clean 2>/dev/null
make 2>/dev/null && echo "✓ Kernel built"
make os.iso 2>/dev/null && echo "✓ ISO created"

echo ""
echo "Launching OS in QEMU..."
echo "(Close QEMU window to exit)"
make run
