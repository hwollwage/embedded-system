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
        Schema::create('gas_readings', function (Blueprint $table) {
            $table->id();
            $table->string("device_id");
            $table->integer("gas_value");
            $table->boolean("alarm");
            $table->string("ip_address");
            $table->integer("wifi_rssi");
            $table->unsignedBigInteger("uptime_ms");
            $table->unsignedInteger("free_heap");
            $table->timestamps();
        });
    }

    /**
     * Reverse the migrations.
     */
    public function down(): void
    {
        Schema::dropIfExists('gas_readings');
    }
};
