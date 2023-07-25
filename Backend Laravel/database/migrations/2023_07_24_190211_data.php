<?php

use Illuminate\Database\Migrations\Migration;
use Illuminate\Database\Schema\Blueprint;
use Illuminate\Support\Facades\Schema;

return new class extends Migration
{
    /**
     * Run the migrations.
     */
    public function up(): void
    {
        Schema::create('data', function (Blueprint $table) {
            $table->bigIncrements('id');
            $table->bigInteger('sensor_id')->unsigned();
            $table->char('user_floor_humidity', 10);
            $table->char('user_atmosphere_humidity', 10);
            $table->char('user_temperature', 10);
            $table->char('user_light', 10);
            $table->char('user_uv', 10);
            $table->timestamps();
            $table->foreign('sensor_id')->references('id')->on('sensor');
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down(): void
    {
        Schema::drop('data');
    }
};
