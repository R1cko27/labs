try {
    std::vector<int> v(1000000000000); // может бросить bad_alloc
} catch (const std::bad_alloc& e) {
    std::cerr << "Memory error: " << e.what() << '\n';
} catch (const std::exception& e) {
    std::cerr << "General error: " << e.what() << '\n';
} catch (...) {
    std::cerr << "Unknown exception\n";
}


// Необрабатываемое исключение — исключение, для которого не нашлось подходящего обработчика catch.