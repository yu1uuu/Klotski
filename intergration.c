void draw_two_grid_box_vertical(struct fb_t *const fbp, int row, int col, int box_idx){

    int x = 55+(col-1)*33;
    int y = 15+(row-1)*33;


    draw_box(fbp, box[box_idx], x, y);
    draw_box(fbp, box[box_idx], x, y+15);
    draw_box(fbp, box[box_idx], x+15, y);
    draw_box(fbp, box[box_idx], x+15, y+15);

    draw_box(fbp, box[box_idx], x+9, y+18);
    draw_box(fbp, box[box_idx], x+6, y+18);

    draw_box(fbp, box[box_idx], x, y+33);
    draw_box(fbp, box[box_idx], x, y+48);
    draw_box(fbp, box[box_idx], x+15, y+33);
    draw_box(fbp, box[box_idx], x+15, y+48);

    if (col > 0 && col <= 6) {
        grid_array[row - 1][col - 1] = 1;
        grid_array[row][col - 1] = 1;
    }
}

void erase_two_grid_box_vertical(struct fb_t *const fbp, int row, int col){

    draw_two_grid_box_vertical(fbp, row, col, 3);

    if (col > 0 && col < 6) {
        grid_array[row - 1][col - 1] = 0;
        grid_array[row][col - 1] = 0;
    }
}

void move_two_grid_box_vertical(int box_id){
    int row = get_row(game, box_id);
    int col = get_col(game, box_id);
    int color = get_color(game, box_id);
    bool highlight = get_highlighted(game, box_id);
    if (highlight){
        color = 4;
    }

    if(up_pressed && row >= 1) {
        if (row > 1 && grid_array[row - 2][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
            draw_two_grid_box_vertical(fbp, row-1, col, color);
            set_row(game, box_id, row-1);
        }
    }else if(down_pressed && row < 5) {
        if (row < 5 && grid_array[row + 1][col - 1] == 0) {
            erase_two_grid_box_vertical(fbp, row, col);
            draw_two_grid_box_vertical(fbp, row+1, col, color);
            set_row(game, box_id, row+1);
        }
    }
}

// ------------------- three grid box horizontal ---------------------

void draw_three_grid_box_horizontal(struct fb_t *const fbp, int row, int col, int box_idx){

    int x = 55+(col-1)*33;
    int y = 15+(row-1)*33;

    draw_box(fbp, box[box_idx], x, y);
    draw_box(fbp, box[box_idx], x, y+15);
    draw_box(fbp, box[box_idx], x+15, y);
    draw_box(fbp, box[box_idx], x+15, y+15);

    draw_box(fbp, box[box_idx], x+18, y+6);
    draw_box(fbp, box[box_idx], x+18, y+9);

    draw_box(fbp, box[box_idx], x+33, y);
    draw_box(fbp, box[box_idx], x+33, y+15);
    draw_box(fbp, box[box_idx], x+48, y);
    draw_box(fbp, box[box_idx], x+48, y+15);

    draw_box(fbp, box[box_idx], x+51, y+6);
    draw_box(fbp, box[box_idx], x+51, y+9);

    draw_box(fbp, box[box_idx], x+66, y);
    draw_box(fbp, box[box_idx], x+66, y+15);
    draw_box(fbp, box[box_idx], x+81, y);
    draw_box(fbp, box[box_idx], x+81, y+15);

    if (col > 0 && col < 6) {
        grid_array[row - 1][col - 1] = 1;
        grid_array[row - 1][col] = 1;
        grid_array[row - 1][col + 1] = 1;
    }
}

void erase_three_grid_box_horizontal(struct fb_t *const fbp, int row, int col){

    draw_three_grid_box_horizontal(fbp, row, col, 3);

    if (col > 0 && col < 6) {
        grid_array[row - 1][col - 1] = 0;
        grid_array[row - 1][col] = 0;
        grid_array[row - 1][col + 1] = 0;
    }
}





void move_three_grid_box_horizontal(int box_id){

    int row = get_row(game, box_id);
    int col = get_col(game, box_id);
    int color = get_color (game, box_id);
    bool highlight = get_highlighted(game, box_id);
    if (highlight){
        color = 4;
    }
    if(left_pressed && col > 1) {
        if(grid_array[row - 1][col - 2] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
            draw_three_grid_box_horizontal(fbp, row, col-1, color);
            set_col(game, box_id, col-1);
        }
    }else if(right_pressed && col < 4) {
        if(grid_array[row - 1][col + 3] == 0) {
            erase_three_grid_box_horizontal(fbp, row, col);
            draw_three_grid_box_horizontal(fbp, row, col+1, color);

            //col +=1

            set_col(game, box_id, col+1);

        }

    }
}


// ------------------- three grid box vertical ---------------------

void draw_three_grid_box_vertical(struct fb_t *const fbp, int row, int col, int box_idx){

    int x = 55+(col-1)*33;
    int y = 15+(row-1)*33;

    draw_box(fbp, box[box_idx], x, y);
    draw_box(fbp, box[box_idx], x, y+15);
    draw_box(fbp, box[box_idx], x+15, y);
    draw_box(fbp, box[box_idx], x+15, y+15);

    draw_box(fbp, box[box_idx], x+9, y+18);
    draw_box(fbp, box[box_idx], x+6, y+18);

    draw_box(fbp, box[box_idx], x, y+33);
    draw_box(fbp, box[box_idx], x, y+48);
    draw_box(fbp, box[box_idx], x+15, y+33);
    draw_box(fbp, box[box_idx], x+15, y+48);

    draw_box(fbp, box[box_idx], x+9, y+51);
    draw_box(fbp, box[box_idx], x+6, y+51);

    draw_box(fbp, box[box_idx], x, y+66);
    draw_box(fbp, box[box_idx], x, y+81);
    draw_box(fbp, box[box_idx], x+15, y+66);
    draw_box(fbp, box[box_idx], x+15, y+81);

    if (col > 0 && col <= 6) {
        grid_array[row - 1][col - 1] = 1;
        grid_array[row][col - 1] = 1;
        grid_array[row + 1][col - 1] = 1;
    }
}

void erase_three_grid_box_vertical(struct fb_t *const fbp, int row, int col){

    draw_three_grid_box_vertical(fbp, row, col, 3);

    if (col > 0 && col < 6) {
        grid_array[row - 1][col - 1] = 0;
        grid_array[row][col - 1] = 0;
        grid_array[row + 1][col - 1] = 0;
    }
}

void move_three_grid_box_vertical(int box_id){

    int row = get_row(game, box_id);
    int col = get_col(game, box_id);
    int color = get_color (game, box_id);
    bool highlight = get_highlighted(game, box_id);
    if (highlight){
        color = 4;
    }
    if(up_pressed && row > 1) {
        if (grid_array[row - 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
            draw_three_grid_box_vertical(fbp, row-1, col, color);
            set_row(game, box_id, row-1);
        }
    }else if(down_pressed && row < 4) {
        if (grid_array[row + 2][col - 1] == 0) {
            erase_three_grid_box_vertical(fbp, row, col);
            draw_three_grid_box_vertical(fbp, row+1, col, color);
            set_row(game, box_id, row+1);
        }
    }
}
