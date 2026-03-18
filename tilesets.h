//
// Created by omgit on 3/18/2026.
//
#pragma once
#include <vector>
#include<string>

// Define our tilesets to randomly generate it.
std::vector<std::vector<std::string>> tileSets =
{
    {// Vertical shelves
        ".#.#.",
        ".#.#.",
        ".#.#.",
        ".#.#.",
        "....." },
    {// Vertical shelves
        ".....",
        ".#.#.",
        ".#.#.",
        ".#.#.",
        ".#.#." },
    {// Vertical shelves
        ".....",
        "#.#.#",
        "#.#.#",
        "#.#.#",
        "....." },
    {// Horizontal shelves
        ".....",
        "####.",
        ".....",
        "####.",
        "....." },
    {// Horizontal shelves
        ".....",
        ".####",
        ".....",
        ".####",
        "....." },
    {// Center aisle
        "##.##",
        "##.##",
        ".....",
        "##.##",
        "##.##" },
    {// Diamond
        "#...#",
        "..#..",
        ".###.",
        "..#..",
        "#...#" },
    {// Open
        ".....",
        ".....",
        "..#..",
        ".....",
        "....." },
    {// open
        ".....",
        "..#..",
        ".....",
        "..#..",
        "....." },
};